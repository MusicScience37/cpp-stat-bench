Writing Custom Main Function
===================================

Runner
---------------

.. doxygenclass:: stat_bench::runner::Runner
    :members: Runner, cli, parse_cli, init, add, run

Benchmark Registry
------------------------

.. doxygenclass:: stat_bench::bench::BenchmarkCaseRegistry
    :members: BenchmarkCaseRegistry, add, instance

Reporter
---------------

.. doxygenclass:: stat_bench::reporter::IReporter

.. doxygenclass:: stat_bench::bench::BenchmarkFullName
    :members: group_name, case_name

.. doxygenclass:: stat_bench::bench::BenchmarkCondition
    :members: threads, params

.. doxygenclass:: stat_bench::param::ParameterDict
    :members: get, format_to, as_string_dict

.. doxygenclass:: stat_bench::measurer::Measurement
    :members: case_info, cond, measurer_name, iterations, samples, durations, durations_stat, custom_stat_outputs, custom_stat, custom_outputs

.. doxygenclass:: stat_bench::stat::Statistics
    :members: unsorted_samples, sorted_samples, mean, max, min, variance, standard_deviation

.. doxygenclass:: stat_bench::clock::SystemTimePoint
    :members: format_to

.. doxygenclass:: stat_bench::clock::Duration

.. doxygentypedef:: stat_bench::clock::TicksCount
