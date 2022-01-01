# Change Log

## On development

### Features

- Public API to get context variable name ([Issue #41](https://gitlab.com/MusicScience37/cpp-stat-bench/-/issues/41)).
- Colored output to console on errors ([Issue #42](https://gitlab.com/MusicScience37/cpp-stat-bench/-/issues/42)).

### Bug Fixes

- Stabilize determination of number of iterations ([Issue #31](https://gitlab.com/MusicScience37/cpp-stat-bench/-/issues/31)).
- Fix parameters in outputs ([Issue #43](https://gitlab.com/MusicScience37/cpp-stat-bench/-/issues/43)).

### Others

- Documentation of APIs for users ([Issue #32](https://gitlab.com/MusicScience37/cpp-stat-bench/-/issues/32)).

## v0.1.0 (2021/12/30)

First release with basic features.

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
