#!/usr/bin/env python3
# verification-helper: IGNORE 1
import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ
from pathlib import Path
from typing import List


logger = getLogger(__name__)  # type: Logger

atcoder_include = re.compile('#include "([a-zA-Z_0-9/]*(|.hpp|))"\s*')

include_guard = re.compile('#.*([A-Z_0-9]_HPP)')
all_include = re.compile('#include <([+a-zA-Z_0-9/]*(|.hpp|.h))>\s*')

lib_path = Path.cwd()

defined = set()
seted = set()


def dfs(f: str) -> List[str]:
    global defined
    if f in defined:
        logger.info('already included {}, skip'.format(f))
        return []
    defined.add(f)

    logger.info('include {}'.format(f))

    with open(file=str(lib_path / f), mode="r", encoding='UTF-8') as f:
        s = f.read()
    result = []
    for line in s.splitlines():
        if include_guard.match(line):
            continue

        m = atcoder_include.match(line)
        m2 = all_include.match(line)
        if m:
            result.extend(dfs(m.group(1)))
            continue
        elif m2:
            target_header = m2.group(1)

            if target_header in seted:
                logger.info('alreay {} , skiped'.format(target_header))
                continue
            logger.info('has {}'.format(target_header))
            seted.add(target_header)
        result.append(line)
    return result


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('-c', '--console',
                        action='store_true', help='Print to Console')
    parser.add_argument('--lib', help='Path to This library Path')
    opts = parser.parse_args()

    if opts.lib:
        lib_path = Path(opts.lib)
    elif 'CPLUS_INCLUDE_PATH' in environ:
        lib_path = Path(environ['CPLUS_INCLUDE_PATH'])
    s = open(opts.source).read()

    result = []
    for line in s.splitlines():
        m = atcoder_include.match(line)
        m2 = all_include.match(line)
        if m:
            result.extend(dfs(m.group(1)))
            continue
        elif m2:
            target_header = m2.group(1)

            if target_header in seted:
                logger.info('alreay {} , skiped'.format(target_header))
                continue
            logger.info('has {}'.format(target_header))
            seted.add(target_header)
        result.append(line)

    output = '\n'.join(result) + '\n'

    if opts.console:
        print(output)
    else:
        with open(file='combined.cpp', mode='w', encoding='UTF-8') as f:
            f.write(output)
        print("out : combined.cpp")
