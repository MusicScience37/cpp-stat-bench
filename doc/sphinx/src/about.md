# About

cpp-stat-bench is a benchmark library with statistics and plotting for C++.

## Features

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

## Origin

I began to write this library because I wanted plots of results,
and I wanted measurements of statistics of processing time
(max, mean, standard deviation, cumulative distribution function, ...)
and precise mean processing time for comparison.
