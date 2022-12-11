# cpp-stat-bench

[![GitLab Release](https://img.shields.io/gitlab/v/release/32226502?sort=semver)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/releases)
[![C++ standard](https://img.shields.io/badge/standard-C%2B%2B14-blue?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/compiler_support/14)
[![pipeline status](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/badges/develop/pipeline.svg)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/commits/develop)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)

Benchmark library with statistics for C++.

## ✨ Features

- Report results in various types of output files.
  - To console.
  - To JSON files.
  - To HTML files of plots 📈.
    - Processing time for each execution.
    - Cumulative distribution function of processing time.
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

- [Documentation build on develop branch](https://cppstatbench.musicscience37.com/)
- Examples are in `examples` directory.

## How to Use

### Via Conan

This library is packaged with [Conan](https://conan.io/),
and available via
[package registry in GitLab](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/packages).

To use this library,
add the package
`cpp_stat_bench/<version>@MusicScience37Projects+utility-libraries+cpp-stat-bench/stable`
with a version you want
to your `conanfile.py` or `conanfile.txt`,
and add the remote
`https://gitlab.com/api/v4/packages/conan`
to conan command.

## How to Build in this Repository

To build this repository,
you will require following dependencies:

- [Python](https://www.python.org/) 3.9
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
    - GCC 10
    - Clang 14
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

2. Add the Conan remote in GitLab. (Once in an environment.)

   ```bash
   conan remote add gitlab https://gitlab.com/api/v4/packages/conan
   ```

3. Download and install required Conan packages.

   ```bash
   mkdir build
   cd build
   conan install --build missing ..
   ```

4. Configure.

   ```bash
   cmake ..
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
