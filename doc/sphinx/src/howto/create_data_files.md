# Create Data Files of Benchmark Results

This section shows how to create data files of benchmark results.

cpp-stat-bench library supports the following formats:

- JSON (via `--json` option)
- [MessagePack](https://msgpack.org/) (via `--msgpack` option)
- Compressed MessagePack (gzip) (via `--compressed-msgpack` option)

## Prerequisites

- Implement a benchmark.

## Sample Code

In this section, a benchmark in
[Implement a Simple Benchmark](../howto/implement_simple_benchmark.md)
is used for demonstration purposes.

## Create a Data File in JSON Format

To create a data file in JSON format, use `--json` option as follows:

```shell
./simple_benchmark --json result.json
```

This command creates a data file named `result.json` in the current directory.
The created file contains the benchmark results in JSON format as follows:

````{toggle}
```json
{
  "$schema": "https://cppstatbench.musicscience37.com/schemas/data_file_schema_v4.json",
  "finished_at": "2025-07-05T15:48:42.298637+0000",
  "measurements": [
    {
      "case_name": "fibonacci(10)",
      "custom_outputs": [],
      "custom_stat_outputs": [],
      "durations": {
        "stat": {
          "max": 1.9799999790848233e-06,
          "mean": 7.704333597757795e-07,
          "median": 6.710000093335111e-07,
          "min": 6.34999992144003e-07,
          "standard_deviation": 3.2653505854796094e-07,
          "standard_error": 5.961687321587306e-08,
          "variance": 1.0662515114541124e-13
        },
        "values": [
          [
            1.1380000159988413e-06,
            7.589999881929543e-07,
            7.05999980255001e-07,
            6.970000185901881e-07,
            6.640000265178969e-07,
            1.9799999790848233e-06,
            6.679999842162943e-07,
            6.829999961155409e-07,
            6.34999992144003e-07,
            6.600000119760807e-07,
            6.849999749647395e-07,
            6.839999855401402e-07,
            6.440000106522348e-07,
            6.450000000768341e-07,
            6.729999881827098e-07,
            6.779999921491253e-07,
            6.490000146186503e-07,
            6.430000212276354e-07,
            6.529999723170476e-07,
            6.679999842162943e-07,
            6.820000066909415e-07,
            1.8709999949351186e-06,
            6.689999736408936e-07,
            6.519999828924483e-07,
            6.77000002724526e-07,
            6.500000040432496e-07,
            6.629999802498787e-07,
            6.930000040483719e-07,
            6.939999934729713e-07,
            6.500000040432496e-07
          ]
        ]
      },
      "group_name": "Fibonacci",
      "iterations": 1,
      "measurement_type": "Processing Time",
      "params": null,
      "samples": 30
    },
    {
      "case_name": "fibonacci(15)",
      "custom_outputs": [],
      "custom_stat_outputs": [],
      "durations": {
        "stat": {
          "max": 8.050999895203859e-06,
          "mean": 5.439666892925743e-06,
          "median": 5.283000064082444e-06,
          "min": 5.236000106378924e-06,
          "standard_deviation": 5.650289267578046e-07,
          "standard_error": 1.0315969234397926e-07,
          "variance": 3.192576682620879e-13
        },
        "values": [
          [
            5.732999852625653e-06,
            5.308999789122026e-06,
            5.253999916021712e-06,
            5.327000053512165e-06,
            8.050999895203859e-06,
            5.287000021780841e-06,
            5.329000032361364e-06,
            5.27300016983645e-06,
            5.297999905451434e-06,
            5.2579998737201095e-06,
            5.2489999688987155e-06,
            5.322000106389169e-06,
            5.283000064082444e-06,
            5.283000064082444e-06,
            5.265999789116904e-06,
            5.265999789116904e-06,
            5.326000064087566e-06,
            5.264999799692305e-06,
            5.306999810272828e-06,
            5.297999905451434e-06,
            6.737000148859806e-06,
            5.281000085233245e-06,
            5.275000148685649e-06,
            5.281000085233245e-06,
            5.259999852569308e-06,
            5.236000106378924e-06,
            5.287000021780841e-06,
            5.277000127534848e-06,
            5.304999831423629e-06,
            5.2669997785415035e-06
          ]
        ]
      },
      "group_name": "Fibonacci",
      "iterations": 1,
      "measurement_type": "Processing Time",
      "params": null,
      "samples": 30
    },
    {
      "case_name": "fibonacci(10)",
      "custom_outputs": [],
      "custom_stat_outputs": [],
      "durations": {
        "stat": {
          "max": 4.965933726452931e-07,
          "mean": 4.595199811774364e-07,
          "median": 4.5548426896857563e-07,
          "min": 4.445828665211593e-07,
          "standard_deviation": 1.475631616898454e-08,
          "standard_error": 2.694122480662031e-09,
          "variance": 2.1774886409814132e-16
        },
        "values": [
          [
            0.034493643790483475,
            0.03499392420053482,
            0.03424959257245064,
            0.03407349810004234,
            0.034107454121112823,
            0.034315213561058044,
            0.034073568880558014,
            0.0358479879796505,
            0.03805742412805557,
            0.03644147142767906,
            0.03647288307547569,
            0.03634115681052208,
            0.03411531448364258,
            0.03629828244447708,
            0.03610967844724655,
            0.03573277220129967,
            0.035623062402009964,
            0.03481997177004814,
            0.03422358259558678,
            0.034106068313121796,
            0.034480199217796326,
            0.034158091992139816,
            0.03422872722148895,
            0.03772161155939102,
            0.035963814705610275,
            0.03438013792037964,
            0.03560575842857361,
            0.03583246469497681,
            0.035548143088817596,
            0.03407149761915207
          ]
        ]
      },
      "group_name": "Fibonacci",
      "iterations": 76637,
      "measurement_type": "Mean Processing Time",
      "params": null,
      "samples": 30
    },
    {
      "case_name": "fibonacci(15)",
      "custom_outputs": [],
      "custom_stat_outputs": [],
      "durations": {
        "stat": {
          "max": 5.16474347023177e-06,
          "mean": 4.871717919741059e-06,
          "median": 4.822026312467642e-06,
          "min": 4.800443093699869e-06,
          "standard_deviation": 9.166041081698495e-08,
          "standard_error": 1.6734825081243798e-08,
          "variance": 8.401630865355943e-15
        },
        "values": [
          [
            0.030078457668423653,
            0.030078014358878136,
            0.03003843128681183,
            0.030211450532078743,
            0.030114153400063515,
            0.03004464879631996,
            0.03166276961565018,
            0.03222283348441124,
            0.03088311478495598,
            0.030675271525979042,
            0.030518490821123123,
            0.030188238248229027,
            0.029982462525367737,
            0.02998678758740425,
            0.03057985194027424,
            0.03005523420870304,
            0.030041249468922615,
            0.029949963092803955,
            0.030026782304048538,
            0.030409060418605804,
            0.031153269112110138,
            0.030090786516666412,
            0.03129732981324196,
            0.030661314725875854,
            0.029983671382069588,
            0.029986022040247917,
            0.029968803748488426,
            0.03092961199581623,
            0.029995545744895935,
            0.030025780200958252
          ]
        ]
      },
      "group_name": "Fibonacci",
      "iterations": 6239,
      "measurement_type": "Mean Processing Time",
      "params": null,
      "samples": 30
    }
  ],
  "started_at": "2025-07-05T15:48:39.586249+0000"
}
```
````

For description of the file format,
see [Schemas](../schemas/index.rst).

## Create a Data File in MessagePack Format

To create a data file in [MessagePack](https://msgpack.org/) format, use `--msgpack` option as follows:

```shell
./simple_benchmark --msgpack result.data
```

This command creates a data file named `result.data` in the current directory.
The created file contains the benchmark results in MessagePack format
with data structure same as JSON format.

## Create a Data File in MessagePack Format with Compression

To create a compressed data file in MessagePack format,
use `--compressed-msgpack` option as follows:

```shell
./simple_benchmark --compressed-msgpack result.data
```

This command creates a data file named `result.data` in the current directory.
The created file is compressed in gzip format.
The compressed contents is same as the data file in MessagePack format.

```{hint}
For example, Python's standard `gzip` package can decompress the compressed data file.
```

## Further Reading

- [Command Line Options](../command_line_options.md)
- [Schemas](../schemas/index.rst)
