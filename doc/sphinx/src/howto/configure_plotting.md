# Configure Plotting in Source Code for More Plots

This section show how to configure plotting in source code to generate more types of plots.

For plots generated without configurations in source codes,
see [Generate Basic Plots of Processing Time](generate_basic_plots.md).

## Prerequisites

- One of the followings:
  - [Implement a Parameterized Benchmark](implement_parameterized_benchmark.md)
  - [Implement a Benchmark with a Custom Output with Statistics](implement_benchmark_with_custom_output_with_stat.md)
  - [Implement a Benchmark with a Custom Output Without Statistics](implement_benchmark_with_custom_output_without_stat.md)
- [Generate Basic Plots of Processing Time](generate_basic_plots.md)

## Sample Code with Explanation

```{literalinclude} ../../../../examples/configure_plotting.cpp
:caption: Example of a benchmark with configuration of plotting.
:language: cpp
:start-at: "#include"
```

## Execution

You can build the above code and run the resulting executable with `--plot` option
as in [Generate Basic Plots of Processing Time](generate_basic_plots.md).

With the configuration in the source code,
more plots are generated in the `results` directory.
Check the generated plots using a web browser.

In the above example, the following plots are generated
(plots added by the configuration are highlighted):

```{uml}
salt
{
{T
 + <color:gray>results
 ++ <color:gray>ApproxExp
 +++ <color:gray>ProcessingTime_samples.html
 +++ <color:gray>ProcessingTime_box.html
 +++ <color:gray>ProcessingTime_violin.html
 +++ <color:gray>ProcessingTime_cdf.html
 +++ <color:#D66D32>ProcessingTime_by_num_terms.html
 +++ <color:#D66D32>ProcessingTime_error_by_num_terms.html
 +++ <color:#D66D32>ProcessingTime_to_error_by_num_terms.html
 +++ <color:gray>MeanProcessingTime_samples.html
 +++ <color:gray>MeanProcessingTime_box.html
 +++ <color:gray>MeanProcessingTime_violin.html
 +++ <color:gray>MeanProcessingTime_cdf.html
 +++ <color:#D66D32>MeanProcessingTime_by_num_terms.html
 +++ <color:#D66D32>MeanProcessingTime_error_by_num_terms.html
 +++ <color:#D66D32>MeanProcessingTime_to_error_by_num_terms.html
}
}
```

## Types of Plots

The following types of plots can be generated:

| Function                                                                                                                                          | Plot Type   | X-axis          | Y-axis          |
| :------------------------------------------------------------------------------------------------------------------------------------------------ | :---------- | :-------------- | :-------------- |
| {cpp:func}`add_parameter_to_time_line_plot <stat_bench::bench_impl::BenchmarkGroupRegister::add_parameter_to_time_line_plot>`                     | Line plot   | Parameter       | Processing time |
| {cpp:func}`add_parameter_to_time_violin_plot <stat_bench::bench_impl::BenchmarkGroupRegister::add_parameter_to_time_line_plot>`                   | Violin plot | Parameter       | Processing time |
| {cpp:func}`add_parameter_to_time_box_plot <stat_bench::bench_impl::BenchmarkGroupRegister::add_parameter_to_time_box_plot>`                       | Box plot    | Parameter       | Processing time |
| {cpp:func}`add_parameter_to_output_line_plot <stat_bench::bench_impl::BenchmarkGroupRegister::add_parameter_to_output_line_plot>`                 | Line plot   | Parameter       | Custom output   |
| {cpp:func}`add_time_to_output_by_parameter_line_plot <stat_bench::bench_impl::BenchmarkGroupRegister::add_time_to_output_by_parameter_line_plot>` | Line plot   | Processing time | Custom output   |

## Further Reading

- API Reference
  - {c:func}`STAT_BENCH_GROUP`
  - {cpp:class}`stat_bench::bench_impl::BenchmarkGroupRegister`
  - {cpp:class}`stat_bench::PlotOption`
