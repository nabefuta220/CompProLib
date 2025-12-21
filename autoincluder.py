#!/usr/bin/env python3
# verification-helper: IGNORE 1
import re
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, path
from pathlib import Path
from typing import List


logger: Logger = getLogger(__name__)


library_include = re.compile('#include "([a-zA-Z_0-9/]*(|.hpp|))"\\s*')

include_guard = re.compile('#.*([A-Z_0-9]_HPP)')
all_include = re.compile('#include <([+a-zA-Z_0-9/]*(|.hpp|.h))>\\s*')

lib_paths = List[Path]

defined: set[str] = set()
included_headers: set[str] = set()


def dfs(f: str) -> List[str]:
    global defined
    global lib_paths
    if f in defined:
        logger.info('already included {}, skip'.format(f))
        return []
    defined.add(f)

    logger.info('include {}'.format(f))
    s = ''
    for lib_path in lib_paths:
        if path.isfile(lib_path/f):
            with open(file=str(lib_path / f), mode="r", encoding='UTF-8') as file:
                s = file.read()
            continue
    if not s:
        raise FileNotFoundError(f"{f} not Found")
    result = []
    for line in s.splitlines():
        if include_guard.match(line):
            continue

        m = library_include.match(line)
        m2 = all_include.match(line)
        if m:
            result.extend(dfs(m.group(1)))
            continue
        elif m2:
            target_header = m2.group(1)

            if target_header in included_headers:
                logger.info('already {} , skipped'.format(target_header))
                continue
            logger.info('has {}'.format(target_header))
            included_headers.add(target_header)
        result.append(line)
    return result


if __name__ == "__main__":
    # logger の設定
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    # 引数の設定
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('-c', '--console',
                        action='store_true', help='Print to Console')
    parser.add_argument(
        '-o', '--output', help='path to output', default='combined.cpp')
    parser.add_argument('--lib', help='Path to This library Path', nargs="*")
    opts = parser.parse_args()

    # ライブラリファイルを取得する
    if opts.lib:
        lib_paths = list(map(Path, opts.lib))
    elif 'CPLUS_INCLUDE_PATH' in environ:
        print(f"{environ['CPLUS_INCLUDE_PATH'].split(":")}")
        lib_paths = list(map(Path, environ['CPLUS_INCLUDE_PATH'].split(':')))

    # 対象ファイルの読み込み
    s = open(opts.source).read()

    result = []
    for line in s.splitlines():
        m = library_include.match(line)
        m2 = all_include.match(line)
        if m:
            result.extend(dfs(m.group(1)))
            continue
        elif m2:
            target_header = m2.group(1)

            if target_header in included_headers:
                logger.info('already {} , skipped'.format(target_header))
                continue
            logger.info('has {}'.format(target_header))
            included_headers.add(target_header)
        result.append(line)

    output = '\n'.join(result) + '\n'

    if opts.console:
        print(output)
    else:
        output_file = opts.output
        with open(file=output_file, mode='w', encoding='UTF-8') as f:
            f.write(output)
        logger.info('out : {}'.format(output_file))
