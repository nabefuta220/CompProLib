#!/usr/bin/env python3
# verification-helper: IGNORE 1
import re
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ
from pathlib import Path
from dataclasses import dataclass, field

RawFileName = str
RawFileNames = list[RawFileName]
SourceLine = str
SourceLines = list[SourceLine]
DefinedParam = str



@dataclass
class IncludeContext:
    """現在読み込まれているヘッダファイルの情報を管理するクラス"""
    lib_paths: list[Path]
    included_local: set[RawFileName] = field(default_factory=set)
    included_system: set[RawFileName] = field(default_factory=set)
    defined_args: set[DefinedParam] = field(default_factory=set)

@dataclass
class SourceFileInfo:
    """現在読んでいるファイルの場所とその内容を取得するクラス"""
    file_path : RawFileName
    line_contents : SourceLine
    line_no: int
    char_no: int = 0
    def __str__(self) -> str:
        return f"{self.file_path}:{self.line_no}:{self.char_no}:"

logger: Logger = getLogger(__name__)


library_include = re.compile('#include "([a-zA-Z_0-9/]*(|.hpp|))"\\s*')

include_guard = re.compile('#.*([A-Z_0-9]_HPP)')
all_include = re.compile('#include <([+a-zA-Z_0-9/]*(|.hpp|.h))>\\s*')

LOCAL_INCLUDE_RE = re.compile(r'#include\s+"([^"]+)"')
SYSTEM_INCLUDE_RE = re.compile(r'#include\s+<([^>]+)>')
INCLUDE_GUARD_RE = re.compile(r'#ifndef\s+([A-Z0-9_]+_HPP)')
DEFINE_PARAM_RE = re.compile(r'#define\s+([A-Z0-9_]+_HPP)')
END_IF_RE = re.compile(r'#endif\s*//*\s*([A-Z0-9_]+_HPP)*')
SINGLE_END_IF_RE = re.compile(r'#endif\s*')


def prepare_args():
    """引数解釈の準備を行う
     Returns:
        argparse.ArgumentParser: 引数解釈器
    """
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('-c', '--console',
                        action='store_true', help='Print to Console')
    parser.add_argument(
        '-o', '--output', help='path to output', default='combined.cpp')
    parser.add_argument('--lib', help='Path to This library Path', nargs="*")
    return parser


def parse_args(parser: argparse.ArgumentParser) -> tuple[RawFileName, bool, RawFileNames, RawFileName]:
    """引数解釈を行う
    Returns:
        tuple: (source_file, is_output_to_console, lib_paths, output_file)
    """
    args = parser.parse_args()

    # source ファイルの処理
    source: RawFileName = args.source
    # console 出力を行うかの処理
    console: bool = False
    if args.console:
        console = True
    # lib パスの処理
    lib: RawFileNames = []
    if args.lib:
        lib = args.lib
    elif 'CPLUS_INCLUDE_PATH' in environ:
        lib = environ['CPLUS_INCLUDE_PATH'].split(':')
    # 現在のディレクトリの位置も追加する
        lib.append(RawFileName(Path.cwd()))
        logger.debug("Resolved library include paths: %s", lib)
    # output ファイルの処理
    if args.output:
        output: RawFileName = args.output
    else:
        output = 'combined.cpp'
    return source, console, lib, output


def build_contest(libs: RawFileNames) -> IncludeContext:
    """IncludeContext を構築する

    Args:
        libs (RawFileNames): ライブラリパスのリスト

    Returns:
        IncludeContext: IncludeContext オブジェクト
    """
    return IncludeContext(lib_paths=list(map(Path, libs)))


def find_file(source: RawFileName, lib_paths: list[Path]) -> Path:
    """ライブラリパスからファイルを探す

    Args:
        source (RawFileName): 探すファイル名
        lib_paths (list[Path]): ライブラリパスのリスト

    Raises:
        FileNotFoundError: ファイルが見つからなかった場合に発生

    Returns:
        RawFileName: 見つかったファイルのパス
    """
    for lib_path in lib_paths:
        file_candidate = lib_path / source
        if file_candidate.is_file():
            return Path(file_candidate)
    raise FileNotFoundError(f"{source} not Found")


def expand_file(
    source: RawFileName,
    ctx: IncludeContext
) -> SourceLines:
    """ファイルを展開する

    Args:
        source (RawFileName): 展開対象のファイル名
        ctx (IncludeContext): IncludeContext オブジェクト

    Returns:
        SourceLines: 展開結果の行リスト
    """
    result: SourceLines = []

    # これから読むファイルは初めてかを確認する
    if source in ctx.included_local:
        logger.info('already included {}, skip'.format(source))
        return result
    ctx.included_local.add(source)
    logger.info('include {}'.format(source))

    # 読み込むファイルのディレクトリを確認する
    s = ''
    lib_file = find_file(source, ctx.lib_paths)
    with open(file=lib_file, mode="r", encoding='UTF-8') as file:
        s = file.read()
    read_info = SourceFileInfo(file_path=source, line_contents=s, line_no=0)
    for line_no,line in enumerate(s.splitlines()):
        read_info.line_no = line_no + 1
        read_info.line_contents = line
        processed_lines = process_line(read_info, ctx)
        result.extend(processed_lines)
    return result


def process_line(source_info: SourceFileInfo, ctx: IncludeContext) -> SourceLines:
    """1行を処理する

    Args:
        line (SourceFileInfo): 処理対象の行
        ctx (IncludeContext): IncludeContext オブジェクト

    Returns:
        SourceLines: 処理結果の行リスト
    """
    result: SourceLines = []
    # 正規表現にマッチするかを確認する
    local_include = LOCAL_INCLUDE_RE.match(source_info.line_contents)
    system_include = SYSTEM_INCLUDE_RE.match(source_info.line_contents)
    include_guard_start = INCLUDE_GUARD_RE.match(source_info.line_contents)
    define_param = DEFINE_PARAM_RE.match(source_info.line_contents)
    end_if = END_IF_RE.match(source_info.line_contents)
    single_end_if = SINGLE_END_IF_RE.match(source_info.line_contents)

    if local_include:
        target_header = local_include.group(1)
        logger.info('local include found: {}'.format(target_header))
        result.extend(expand_file(target_header, ctx))
    elif system_include:
        target_header = system_include.group(1)
        if target_header in ctx.included_system:
            logger.info('already {} , skipped'.format(target_header))
        else:
            logger.info('has {}'.format(target_header))
            ctx.included_system.add(target_header)
            result.append(source_info.line_contents)
    elif include_guard_start:
        guard_name = include_guard_start.group(1)
        logger.info('include guard start found ({})'.format(guard_name))
        result.append(source_info.line_contents)
    elif define_param:
        param_name = define_param.group(1)
        logger.info('define param found ({})'.format(param_name))
        result.append(source_info.line_contents)

    elif end_if:
        guard_name = end_if.group(1)
        logger.info('end if found ({})'.format(guard_name))
        result.append(source_info.line_contents)
    elif single_end_if:
        logger.warning('single end if found!')
        result.append(source_info.line_contents)
    else:
        result.append(source_info.line_contents)
    return result


def write_output(output_line: SourceLines, is_output_to_console: bool, output_file: RawFileName) -> None:
    """出力をファイルまたはコンソールに書き込む

    Args:
        output_line (SourceLines): 出力内容の行リスト
        is_output_to_console (bool): コンソールに出力するかどうか
        output_file (RawFileName): 出力ファイルパス
    """
    output = '\n'.join(output_line) + '\n'
    if is_output_to_console:
        print(output)
    else:
        with open(file=output_file, mode='w', encoding='UTF-8') as f:
            f.write(output)
        logger.info('out : {}'.format(output_file))


if __name__ == "__main__":

    # logger の設定
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    # 引数の設定
    arg_parser = prepare_args()

    source_file, is_output_to_console, lib_paths, output_file = parse_args(
        arg_parser)
    include_context = build_contest(libs=lib_paths)
    expand_result = expand_file(source_file, include_context)
    write_output(expand_result, is_output_to_console, output_file)
