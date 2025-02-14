# Implement a Parameterized Benchmark

This section shows how to implement a parameterized benchmark using cpp-stat-bench library.

## Prerequisites

- [Install cpp-stat-bench](../installation.md)
- [Implement a Simple Benchmark](implement_simple_benchmark.md)

## Sample Code with Explanation

```{literalinclude} ../../../../examples/parameterized_benchmark.cpp
:caption: Example of a parameterized benchmark.
:language: cpp
:start-at: "#include"
```

## Execution

You can build the above code and run the resulting executable without arguments
to see an output similar to the one below.

```{code-block} none
:caption: Example output to the console.

cpp-stat-bench 0.21.0

Benchmark start at 2025-02-13T11:46:03.631299+0000

Time resolution: 1.000e-09 sec.

========================================================================================================================
Processing Time
========================================================================================================================

>> Fibonacci
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
fibonacci (number=10)                                                1     100     0.1299    0.0004    0.1610
fibonacci (number=15)                                                1     100     1.2954    0.0142    2.6950

========================================================================================================================
Mean Processing Time
========================================================================================================================

>> Fibonacci
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
fibonacci (number=10)                                           315663      30     0.1153    0.0005    0.1214
fibonacci (number=15)                                            26556      30     1.3075    0.0062    1.4165

Benchmark finished at 2025-02-13T11:46:06.793683+0000
```

## Further Reading

- API Reference
  - {cpp:class}`stat_bench::FixtureBase`
  - {c:func}`STAT_BENCH_CASE_F`
  - {cpp:func}`stat_bench::current_invocation_context`
  - {cpp:func}`stat_bench::InvocationContext::get_param`
- [Generate Basic Plots of Processing Time](generate_basic_plots.md)
- [Configure Plotting in Source Code for More Plots](configure_plotting.md)
