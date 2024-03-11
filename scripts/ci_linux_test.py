#!/usr/bin/env python3
"""Script run in CI for tests in Linux."""

import os
import subprocess
import typing

import click

BUILD_TYPE_DICT = {
    "debug": "Debug",
    "release": "Release",
    "asan_ubsan": "Debug",
    "tsan": "Debug",
}


TEST_TYPE_VARIABLES = {
    "debug": {
        "STAT_BENCH_TESTING": "ON",
        "STAT_BENCH_ENABLE_BENCH": "ON",
        "STAT_BENCH_TEST_BENCHMARKS": "ON",
        "STAT_BENCH_BUILD_EXAMPLES": "ON",
        "STAT_BENCH_TEST_EXAMPLES": "ON",
    },
    "release": {
        "STAT_BENCH_TESTING": "ON",
        "STAT_BENCH_BUILD_EXAMPLES": "ON",
        "STAT_BENCH_TEST_EXAMPLES": "ON",
    },
    "asan_ubsan": {
        "STAT_BENCH_TESTING": "ON",
        "STAT_BENCH_ENABLE_BENCH": "ON",
        "STAT_BENCH_TEST_BENCHMARKS": "ON",
        "STAT_BENCH_BUILD_EXAMPLES": "ON",
        "STAT_BENCH_TEST_EXAMPLES": "ON",
    },
    "tsan": {
        "STAT_BENCH_TESTING": "ON",
        "STAT_BENCH_ENABLE_BENCH": "ON",
        "STAT_BENCH_TEST_BENCHMARKS": "ON",
        "STAT_BENCH_BUILD_EXAMPLES": "ON",
        "STAT_BENCH_TEST_EXAMPLES": "ON",
    },
}


def execute_command(command: typing.List[str], cwd: str) -> None:
    click.echo(click.style(f">> {command}", bold=True, fg="green"))
    subprocess.run(command, check=True, cwd=cwd)


@click.command()
@click.option("--compiler_type", "compiler_type", required=True)
@click.option("--test_type", "test_type", required=True)
@click.option("--cpp_ver", "cpp_ver", required=True)
@click.option("--build_dir", "build_dir", required=True)
def check_tests_for_condition(
    compiler_type: str,
    test_type: str,
    cpp_ver: str,
    build_dir: str,
) -> None:
    os.makedirs(build_dir, exist_ok=True)

    # Configure
    command = [
        "cmake",
        "..",
        "-G",
        "Ninja",
        "-DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake",
    ]
    build_type = BUILD_TYPE_DICT[test_type]
    command = command + [f"-DCMAKE_BUILD_TYPE={build_type}"]
    if compiler_type.startswith("clang"):
        if test_type == "asan_ubsan":
            command = command + [
                "-DVCPKG_TARGET_TRIPLET=x64-linux-llvm",
                "-DVCPKG_HOST_TRIPLET=x64-linux-llvm",
                "-DCMAKE_CXX_FLAGS=-stdlib=libc++ -fsanitize=address,undefined",
                "-DCMAKE_MODULE_LINKER_FLAGS=-fsanitize=address,undefined",
            ]
        elif test_type == "tsan":
            command = command + [
                "-DVCPKG_TARGET_TRIPLET=x64-linux-llvm",
                "-DVCPKG_HOST_TRIPLET=x64-linux-llvm",
                "-DCMAKE_CXX_FLAGS=-stdlib=libc++ -fsanitize=thread",
                "-DCMAKE_MODULE_LINKER_FLAGS=-fsanitize=thread",
            ]
        else:
            command = command + [
                "-DVCPKG_TARGET_TRIPLET=x64-linux-llvm",
                "-DVCPKG_HOST_TRIPLET=x64-linux-llvm",
                "-DCMAKE_CXX_FLAGS=-stdlib=libc++",
            ]
    command = command + ["-DSTAT_BENCH_ENABLE_CCACHE:BOOL=ON"]
    command = command + ["-DSTAT_BENCH_WRITE_JUNIT:BOOL=ON"]
    command = command + [f"-DCMAKE_CXX_STANDARD={cpp_ver}"]
    for key, value in TEST_TYPE_VARIABLES[test_type].items():
        command = command + [f"-D{key}={value}"]
    execute_command(command, cwd=build_dir)

    # Build
    execute_command(["cmake", "--build", "."], cwd=build_dir)

    # Test
    execute_command(["ctest", "-V"], cwd=build_dir)


if __name__ == "__main__":
    check_tests_for_condition()
