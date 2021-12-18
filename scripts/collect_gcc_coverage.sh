#!/bin/bash -e

# usage: collect_gcc_coverage.sh <build directory>

DIR=$1

mkdir $DIR/coverage
COV=$DIR/coverage/coverage
HTML=$DIR/coverage/html
ROOT=$(realpath $(dirname $(dirname $0)))

lcov --rc lcov_branch_coverage=1 --directory ./ --capture --output-file $COV
lcov --rc lcov_branch_coverage=1 --extract $COV "${ROOT}/include/*" --output-file $COV
genhtml --rc lcov_branch_coverage=1 --output-directory $HTML $COV
lcov --rc lcov_branch_coverage=1 --list $COV
