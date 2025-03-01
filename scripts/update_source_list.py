#!/usr/bin/env python3
"""Helper script to create lists of source codes for build."""

import subprocess
from pathlib import Path

THIS_DIR = Path(__file__).parent.absolute()

SOURCE_PATHS = [
    THIS_DIR.parent / "src" / "stat_bench",
    THIS_DIR.parent / "tests" / "units",
]

UNITY_SRC_SUFFIX = "unity_source.cpp"
SOURCE_LIST_CMAKE_SUFFIX = "source_list.cmake"


def list_source_files(base_dir: Path) -> list[Path]:
    """List source files.

    Args:
        base_dir (Path): Base directory.

    Returns:
        list[Path]: Paths of source files.
    """

    files = []
    for child in base_dir.iterdir():
        if child.is_dir():
            files = files + list_source_files(child)
        elif child.is_file() and str(child.suffix) == ".cpp":
            files = files + [child]
    return files


def list_source_file_paths(base_path: Path) -> list[str]:
    """List source files in unit test.

    Args:
        base_dir (Path): Base directory.

    Returns:
        list[str]: Paths of source files.
    """

    source_files = list_source_files(base_path)
    return sorted(
        [
            str(source_file.relative_to(base_path)).replace("\\", "/")
            for source_file in source_files
            if str(source_file) != str(base_path / UNITY_SRC_SUFFIX)
        ]
    )


def write_unity_source(base_path: Path, file_paths: list[str]):
    """Write unity source file.

    Args:
        base_dir (Path): Base directory.
        file_paths (list[str]): Paths of source files.
    """

    unity_src_path = base_path / UNITY_SRC_SUFFIX
    with open(str(unity_src_path), mode="w", encoding="ascii", newline="\n") as file:
        for source_file in file_paths:
            file.write(
                f'#include "{source_file}" // NOLINT(bugprone-suspicious-include)\n'
            )

    subprocess.run(["clang-format", "-i", str(unity_src_path)], check=True)


def write_cmake_var_file(base_path: Path, file_paths: list[str]):
    """Write CMake script of source files.

    Args:
        base_dir (Path): Base directory.
        file_paths (list[str]): Paths of source files.
    """

    source_list_cmake_path = base_path / SOURCE_LIST_CMAKE_SUFFIX
    with open(
        str(source_list_cmake_path), mode="w", encoding="ascii", newline="\n"
    ) as file:
        file.write("set(SOURCE_FILES\n")
        for source_file in file_paths:
            file.write(f"    {source_file}\n")
        file.write(")\n")


def main():
    """Main function"""

    for base_path in SOURCE_PATHS:
        file_paths = list_source_file_paths(base_path)
        write_unity_source(base_path, file_paths)
        write_cmake_var_file(base_path, file_paths)


if __name__ == "__main__":
    main()
