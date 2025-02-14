# Generate Basic Plots of Processing Time

This section shows how to generate basic plots of processing time using cpp-stat-bench library.

cpp-stat-bench library can generate some plots of processing time
without configurations in source codes.

## Prerequisites

- Implement a benchmark.

## Sample Code

In this section, a benchmark in
[Implement a Simple Benchmark](../howto/implement_simple_benchmark.md)
is used for demonstration purposes.

## Generate Plots

To create plots, use `--plot` option as follows:

```shell
./simple_benchmark --plot results
```

This command generates plots of processing time in the `results` directory.
Plots are generated for each group of benchmarks as follows:

```{uml}
salt
{
{T
 + results                              | (Directory specified in command line option.)
 ++ <benchmark_group_name>              | (Directory per group of benchmarks.)
 +++ ProcessingTime_samples.html        | (Plots. See below for details.)
 +++ ProcessingTime_box.html
 +++ ProcessingTime_violin.html
 +++ ProcessingTime_cdf.html
 +++ MeanProcessingTime_samples.html
 +++ MeanProcessingTime_box.html
 +++ MeanProcessingTime_violin.html
 +++ MeanProcessingTime_cdf.html
}
}
```

Here describes the plots generated:

| File Name                         | Description                                               | X-axis               | Y-axis                 |
| :-------------------------------- | :-------------------------------------------------------- | :------------------- | :--------------------- |
| `ProcessingTime_samples.html`     | Line plot of processing time.                             | Sample index         | Processing time        |
| `ProcessingTime_box.html`         | Box plot of processing time.                              | Case of benchmark    | Processing time        |
| `ProcessingTime_violin.html`      | Violin plot of processing time.                           | Case of benchmark    | Processing time        |
| `ProcessingTime_cdf.html`         | Cumulative distribution function of processing time.      | Processing time      | Cumulative probability |
| `MeanProcessingTime_samples.html` | Line plot of mean processing time.                        | Sample index         | Mean processing time   |
| `MeanProcessingTime_box.html`     | Box plot of mean processing time.                         | Case of benchmark    | Mean processing time   |
| `MeanProcessingTime_violin.html`  | Violin plot of mean processing time.                      | Case of benchmark    | Mean processing time   |
| `MeanProcessingTime_cdf.html`     | Cumulative distribution function of mean processing time. | Mean processing time | Cumulative probability |

Plots are written in HTML format.
You can view them in a web browser.

```{hint}
When you view plots, the browser needs access to the internet to load JavaScript libraries.
```

## Further Reading

- [Command Line Options](../command_line_options.md)
- [Configure Plotting in Source Code for More Plots](configure_plotting.md)
