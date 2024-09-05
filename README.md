# cpp-stat-bench

[![GitLab Release](https://img.shields.io/gitlab/v/release/32226502?sort=semver)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/releases)
[![C++ standard](https://img.shields.io/badge/standard-C%2B%2B14-blue?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/compiler_support/14)
[![pipeline status](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/badges/main/pipeline.svg)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/commits/main)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)

Benchmark library with statistics and plotting in C++.

## ✨ Features

- Report results in various types of output files.
  - To console.
  - To JSON files.
  - To MessagePack files with or without gzip compression.
  - To HTML files of plots 📈.
    - Processing time for each execution.
    - Cumulative distribution function of processing time.
    - Violin plots.
- Measure processing time in two patterns.
  - Processing time of each execution.
  - Mean processing time of consecutive executions.
- Report custom data with or without statistics.
- Use custom parameters in various types.
- Perform benchmark in multiple threads.
- Use fixtures.

## Repositories

- Main in GitLab: [https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench)
- Mirror in GitHub: [https://github.com/MusicScience37/cpp-stat-bench](https://github.com/MusicScience37/cpp-stat-bench)

## Documentation

- [Documentation build on main branch](https://cppstatbench.musicscience37.com/)
- Examples are in `examples` directory.

## Installation

### Via vcpkg

This library can be installed via vcpkg using following configurations:

- Add a vcpkg registry
  `https://gitlab.com/MusicScience37Projects/vcpkg-registry`
  in `vcpkg-configuration.json`.

  Example:

  ```json
  {
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg-configuration.schema.json",
    "default-registry": {
      "kind": "git",
      "repository": "https://github.com/Microsoft/vcpkg",
      "baseline": "099fb9250d916511782bf5215f01f2e7141beb3a"
    },
    "registries": [
      {
        "kind": "git",
        "repository": "https://gitlab.com/MusicScience37Projects/vcpkg-registry",
        "baseline": "fb3ea2e761fca69a7e9cf0a447538792d0cc6057",
        "packages": ["cpp-msgpack-light", "cpp-stat-bench"]
      }
    ]
  }
  ```

- Add `cpp-stat-bench` in `vcpkg.json`

  Example:

  ```json
  {
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
    "dependencies": ["cpp-stat-bench"]
  }
  ```

## How to Build in this Repository

To build this repository,
you will require following dependencies:

- [Python](https://www.python.org/) 3.12
  - You may want to use [pyenv](https://github.com/pyenv/pyenv).
- [poetry](https://python-poetry.org)
  - Required Python packages can be installed using poetry.
    Execute the command `poetry install` on this directory.
  - [pre-commit](https://pre-commit.com/)
    will be installed via poetry, and used for some checks.
    Execute `poetry run pre-commit install` on this directory
    if you develop this library.
- [CMake](https://cmake.org/)
- C++ 14 Compiler
  - Following compilers are tested in CI:
    - GCC 12
    - Clang 18
    - MSVC 19

Additionally, you will require following dependencies
to build documentation.

- [Doxygen](https://www.doxygen.nl/index.html)
- [Graphviz](https://graphviz.org/)
- [PlantUML](https://plantuml.com)
  - Set `PLANTUML_JAR_PATH` environment variable to specify the place of `plantuml.jar` file.
- Java runtime environment (JRE) for PlantUML

After installing the above dependencies,
execute the following commands:

1. Start a shell of poetry.

   ```bash
   cd <this-directory>
   poetry install
   poetry shell
   ```

2. Download vcpkg if you haven't already.

   ```bash
   git submodule update --init
   ```

3. Build vcpkg.

   - On Windows:

     ```bat
     .\vcpkg\bootstrap-vcpkg.bat
     ```

   - On Linux:

     ```bash
     ./vcpkg/bootstrap-vcpkg.sh
     ```

4. Configure.

   ```bash
   mkdir build
   cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
   ```

5. Optionally edit options.

   ```bash
   <some-editor> CMakeCache.txt
   ```

6. Build.

   ```bash
   cmake --build .
   ```

7. Optionally run tests.

   ```bash
   ctest
   ```

## License

This project is licensed under [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).
