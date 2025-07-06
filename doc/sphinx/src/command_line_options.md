# Command Line Options

Currently, the following command line options are available:

```{literalinclude} ../../../tests/integ/approvals/TestCommandLine.test_help.approved.txt
:caption: Help message in console.
:language: none
:start-after: "stdout:"
:end-before: "stderr:"
```

## Options for Plotting

`--plot` option enables generation of plots for benchmark results.

```{seealso}
See [Generate Basic Plots of Processing Time](howto/generate_basic_plots.md) for more details.
```

## Options for Creating Data Files

Following options generates data files of benchmark results in some formats.

| Option                 | Output Format                     |
| :--------------------- | :-------------------------------- |
| `--json`               | JSON                              |
| `--msgpack`            | MessagePack                       |
| `--compressed-msgpack` | MessagePack with gzip compression |

```{seealso}
See [Create Data Files of Benchmark Results](howto/create_data_files.md) for more details.
```

## Options for Configuration of Measurements

Following options set parameters for measurements.

| Option                          | Description                                                                                               |
| :------------------------------ | :-------------------------------------------------------------------------------------------------------- |
| `--samples`                     | Number of samples for measurements of processing time. Default is 30.                                     |
| `--min_sample_duration`         | Minimum duration of a sample for measurement of mean processing time in seconds. Default is 0.03 seconds. |
| `--min_warming_up_iterations`   | Minimum number of iterations for warming up. Default is 1.                                                |
| `--min_warming_up_duration_sec` | Minimum duration for warming up in seconds. Default is 0.03 seconds.                                      |

## Options to Select Benchmarks

Options `--include` and `--exclude` specify benchmarks to include or exclude
in execution using glob patterns.
Current implementation allows use of `*` wildcard in the patterns.

Options `--include_regex` and `--exclude_regex` specify benchmarks to include or exclude
in execution using regular expressions.
Current implementation uses C++'s [modified ECMAScript regular expression](https://en.cppreference.com/w/cpp/regex/ecmascript.html).
