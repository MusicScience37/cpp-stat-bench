@echo off

rem Usage: clang-tidy-tee.bat <path to compile_commands.json> <checked source file> <output file>

clang-tidy -config= --quiet -p=%1 %2 > %3
cd %~dp3
type %~nx3
