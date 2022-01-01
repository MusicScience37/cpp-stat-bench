#!/bin/bash -e

# usage: collect_llvm_coverage.sh <directory of .profraw files>

# ctest must have been called with LLVM_PROFILE_FILE=<build directory>/coverage/coverage_%p.profraw

DIR=$1

# make a file for codecov
llvm-profdata merge -o $DIR/coverage/coverage.profdata $DIR/coverage/coverage_*.profraw
for a in $(find $DIR/bin/stat_bench_test_units); do
    opts="$opts -object $a"
done
llvm-cov show -ignore-filename-regex='(test|.conan)/*' -instr-profile=$DIR/coverage/coverage.profdata $opts \
    >$DIR/coverage/coverage.txt
llvm-cov show -ignore-filename-regex='(test|.conan)/*' -instr-profile=$DIR/coverage/coverage.profdata $opts \
    -format=html -output-dir=$DIR/coverage/html

# output summary to stdout
llvm-cov report -ignore-filename-regex='(test|.conan)/*' -instr-profile=$DIR/coverage/coverage.profdata $opts |
    tee $DIR/coverage/coverage_summary.txt
