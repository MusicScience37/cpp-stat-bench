# Implement a Benchmark with a Custom Output with Statistics

This section shows how to implement a benchmark with a custom output
with statistics using cpp-stat-bench library.

```{hint}
If your custom output doesn't change in each iteration, you should
[implement a benchmark with a custom output without statistics](implement_benchmark_with_custom_output_without_stat.md).
```

## Prerequisites

- [Install cpp-stat-bench](../installation.md)
- [Implement a Simple Benchmark](implement_simple_benchmark.md)
- [Implement a Parameterized Benchmark](implement_parameterized_benchmark.md)
  - The example in this section uses parameters.

## Sample Code with Explanation

```{literalinclude} ../../../../examples/custom_output_with_stat.cpp
:caption: Example of a benchmark with a custom output with statistics.
:language: cpp
:start-at: "#include"
```

## Execution

You can build the above code and run the resulting executable without arguments
to see an output similar to the one below.

```{code-block} none
:caption: Example output to the console.

cpp-stat-bench 0.21.0

Benchmark start at 2025-02-13T14:03:35.480786+0000

Time resolution: 1.000e-09 sec.

========================================================================================================================
Processing Time
========================================================================================================================

>> ApproxPi
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
approx_pi (num_points=100)                                           1     100     5.3556    0.0630   10.0730 error=1.170e-01,
approx_pi (num_points=1000)                                          1     100    12.6330    0.2983   35.7360 error=3.656e-02,
approx_pi (num_points=10000)                                         1     100    98.4151    0.1109       104 error=1.194e-02,

========================================================================================================================
Mean Processing Time
========================================================================================================================

>> ApproxPi
                                                                                Time [us]
                                                            Iterations Samples       Mean Std. Err.       Max Custom Outputs (mean)
------------------------------------------------------------------------------------------------------------------------
approx_pi (num_points=100)                                        7198      30     4.5389    0.0165    4.8675 error=1.317e-01,
approx_pi (num_points=1000)                                       2884      30    12.4647    0.0464   12.9911 error=4.141e-02,
approx_pi (num_points=10000)                                       378      30    89.6876    0.4341   97.2853 error=1.304e-02,

Benchmark finished at 2025-02-13T14:03:39.836305+0000
```

## Further Reading

- API Reference
  - {cpp:func}`stat_bench::current_invocation_context`
  - {cpp:func}`stat_bench::InvocationContext::add_custom_stat`
  - {cpp:class}`stat_bench::stat::CustomStatOutput`
- [Implement a Benchmark with a Custom Output without Statistics](implement_benchmark_with_custom_output_without_stat.md)
- [Generate Basic Plots of Processing Time](generate_basic_plots.md)
- [Configure Plotting in Source Code for More Plots](configure_plotting.md)
