#!/bin/bash

set -e

cd $(dirname $(dirname $0))
iwyu_tool.py -p ./build/Debug -- -isystem /usr/lib/llvm-12/include/c++/v1 | tee ./build/Debug/iwyu_output.txt
fix_includes.py < ./build/Debug/iwyu_output.txt
