# cpp-stat-bench

[![Latest Release](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/badges/release.svg)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/releases)
[![C++ standard](https://img.shields.io/badge/standard-C%2B%2B14-blue?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/compiler_support/14)
[![pipeline status](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/badges/main/pipeline.svg)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/-/commits/main)
[![coverage report](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench/badges/main/coverage.svg)](https://cppstatbench.musicscience37.com/coverage/)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)

A benchmark library with statistical analysis and plotting capabilities in C++.

## ✨ Features

- Report results in various types of output files.
  - To console.
  - To JSON files.
  - To MessagePack files with or without gzip compression.
  - To HTML files of plots 📈.
    - Processing time for each execution.
    - Cumulative distribution function of processing time.
    - Violin plots.
    - Box plots.
    - Plots of processing time with respect to parameters.
    - Plots of custom outputs with respect to parameters.
    - Plots of custom outputs with respect to processing time.
- Measure processing time in two patterns.
  - Processing time of each execution.
  - Mean processing time of consecutive executions.
- Report custom data with or without statistics.
- Use custom parameters in various types.
- Perform benchmark in multiple threads.
- Use fixtures.

## Supported Compilers

This library should compile with most C++ 17 compliant compilers.

Following compilers are tested in CI:

- GCC 13
- Clang 19
- Clang 20
- Visual Studio 2022

## Dependencies

- [fmt](https://github.com/fmtlib/fmt)
- [lyra](https://github.com/bfgroup/Lyra)
- [cpp-msgpack-light](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-msgpack-light)
- [cpp-plotly-plotter](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter)
- [Eigen](https://gitlab.com/libeigen/eigen)
- [yyjson](https://github.com/ibireme/yyjson)
- [nlohmann/json](https://github.com/nlohmann/json)
- [simdutf](https://github.com/simdutf/simdutf)
- [zlib](https://github.com/madler/zlib)

## Installation

See [Install This Library](doc/sphinx/src/installation.md).

## Documentation

Documentation built in CI:

| Version     | Documentation                                                     | Full API Reference (Doxygen)                                          |
| :---------- | :---------------------------------------------------------------- | :-------------------------------------------------------------------- |
| main branch | [Documentation](https://cppstatbench.musicscience37.com/)         | [API Reference](https://cppstatbench.musicscience37.com/api/)         |
| v0.25.2     | [Documentation](https://cppstatbench.musicscience37.com/v0.25.2/) | [API Reference](https://cppstatbench.musicscience37.com/v0.25.2/api/) |

## Repositories

- Main in GitLab: [https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench)
- Mirror in GitHub: [https://github.com/MusicScience37/cpp-stat-bench](https://github.com/MusicScience37/cpp-stat-bench)

## For Developers

- [How to build in this repository](doc/sphinx/src/how_to_build_in_repository.md)

## License

This project is licensed under [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).
