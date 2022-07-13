#!/usr/bin/env python3
"""Helper script to install dependent Conan packages.
"""

from pathlib import Path
import subprocess
from sys import argv
from typing import Iterable
import os

THIS_DIR = Path(__file__).absolute().parent


def make_build_path(build_type: str) -> str:
    """Make the path of the build directory.

    Args:
        build_type (str): Type of build.

    Returns:
        str: Path.
    """

    return str(THIS_DIR.parent / "build" / build_type)


def install_conan_dependencies(build_type: str, *additional_args: Iterable[str]):
    """Install dependent Conan packages.

    Args:
        build_type (str): Type of build.
        additional_args (List[str]): Additional command line arguments.
    """

    build_path = make_build_path(build_type)

    os.makedirs(build_path, exist_ok=True)

    command = (
        [
            "conan",
            "install",
            "--build",
            "missing",
            "-s",
            "build_type=" + build_type,
            "-o",
            "requirements_for_tests=True",
        ]
        + list(additional_args)
        + [
            "../..",
        ]
    )
    print(f"> run command: {command}")
    result = subprocess.run(command, check=False, cwd=build_path)

    exit(result.returncode)


if __name__ == "__main__":
    if len(argv) == 1:
        print(f"Usage: python3 {argv[0]} <build_type> <optional_additional_args>...")
        exit(1)

    install_conan_dependencies(*(argv[1:]))
