# Implement a Benchmark with a Custom Output Without Statistics

This section shows how to implement a benchmark with a custom output
without statistics using cpp-stat-bench library.

```{hint}
If your custom output changes in each iteration, you should
[implement a benchmark with a custom output with statistics](implement_benchmark_with_custom_output_with_stat.md).
```

## Prerequisites

- [Install cpp-stat-bench](../installation.md)
- [Implement a Simple Benchmark](implement_simple_benchmark.md)
- [Implement a Parameterized Benchmark](implement_parameterized_benchmark.md)
  - The example in this section uses parameters.

## Sample Code with Explanation

```{literalinclude} ../../../../examples/custom_output_without_stat.cpp
:caption: Example of a benchmark with a custom output without statistics.
:language: cpp
:start-at: "#include"
```

## Execution

You can build the above code and run the resulting executable without arguments
to see an output similar to the one below.

```{code-block} none
:caption: Example output to the console.

cpp-stat-bench 0.21.0

Benchmark start at 2025-02-13T13:35:41.832607+0000

Time resolution: 1.000e-09 sec.

========================================================================================================================
Processing Time
========================================================================================================================

>> ApproxExp
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
approx_exp (num_terms=1)                                             1     100     0.0367    0.0005    0.0810 error=1.718e+00,
approx_exp (num_terms=2)                                             1     100     0.0352    0.0141    1.4270 error=7.183e-01,
approx_exp (num_terms=5)                                             1     100     0.0248    0.0002    0.0360 error=9.948e-03,
approx_exp (num_terms=10)                                            1     100     0.0299    0.0002    0.0500 error=3.029e-07,

========================================================================================================================
Mean Processing Time
========================================================================================================================

>> ApproxExp
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
approx_exp (num_terms=1)                                       1000000      30     0.0010    0.0000    0.0012 error=1.718e+00,
approx_exp (num_terms=2)                                       1000000      30     0.0022    0.0000    0.0023 error=7.183e-01,
approx_exp (num_terms=5)                                       1000000      30     0.0040    0.0000    0.0043 error=9.948e-03,
approx_exp (num_terms=10)                                      1000000      30     0.0088    0.0000    0.0095 error=3.029e-07,

Benchmark finished at 2025-02-13T13:35:42.799000+0000
```

## Further Reading

- API Reference
  - {cpp:func}`stat_bench::current_invocation_context`
  - {cpp:func}`stat_bench::InvocationContext::add_custom_output`
- [Implement a Benchmark with a Custom Output with Statistics](implement_benchmark_with_custom_output_with_stat.md)
- [Generate Basic Plots of Processing Time](generate_basic_plots.md)
- [Configure Plotting in Source Code for More Plots](configure_plotting.md)
