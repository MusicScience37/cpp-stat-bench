# Implement a Simple Benchmark

This section shows how to implement a simple benchmark using cpp-stat-bench library.

## Prerequisites

- [Install cpp-stat-bench](../installation.md)

## Sample Code with Explanation

```{literalinclude} ../../../../examples/simple_benchmark.cpp
:caption: Example of a simple benchmark.
:language: cpp
:start-at: "#include"
```

## Execution

You can build the above code and run the resulting executable without arguments
to see an output similar to the one below.

```{code-block} none
:caption: Example output to the console.

cpp-stat-bench 0.21.0

Benchmark start at 2025-02-11T14:12:34.660223+0000

Time resolution: 1.000e-09 sec.

========================================================================================================================
Processing Time
========================================================================================================================

>> Fibonacci
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
fibonacci(10)                                                        1     100     0.1431    0.0008    0.2140
fibonacci(15)                                                        1     100     1.4411    0.0207    3.4840

========================================================================================================================
Mean Processing Time
========================================================================================================================

>> Fibonacci
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
fibonacci(10)                                                  1000000      30     0.0009    0.0000    0.0011
fibonacci(15)                                                  1000000      30     0.0012    0.0000    0.0016

Benchmark finished at 2025-02-11T14:12:36.373433+0000
```

## Further Reading

- API Reference
  - {c:func}`STAT_BENCH_CASE`
  - {c:func}`STAT_BENCH_MEASURE`
  - {c:func}`STAT_BENCH_MAIN`
- [Generate Basic Plots of Processing Time](generate_basic_plots.md)
