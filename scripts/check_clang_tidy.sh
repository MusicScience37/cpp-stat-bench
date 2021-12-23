#!/bin/bash

lines=($(cat $(find $1 -name '*.txt') | wc -l))

if [ "$lines" = "0" ]; then
    echo "no warnings in clang-tidy"
    exit 0
else
    echo "some warnings in clang-tidy"
    cat $(find $1 -name '*.txt')
    exit 1
fi
