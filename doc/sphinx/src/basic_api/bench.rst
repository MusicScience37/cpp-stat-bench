Writing Benchmarks
=====================================

Macros to Define and Configure Benchmarks
--------------------------------------------

.. doxygendefine:: STAT_BENCH_CASE

.. doxygendefine:: STAT_BENCH_CASE_F

.. doxygendefine:: STAT_BENCH_MEASURE

.. doxygendefine:: STAT_BENCH_MEASURE_INDEXED

.. doxygendefine:: STAT_BENCH_GROUP

.. doxygendefine:: STAT_BENCH_MAIN

Invocation Context
-------------------------------

.. doxygenfunction:: stat_bench::current_invocation_context

.. doxygenclass:: stat_bench::InvocationContext
    :members: threads, iterations, samples, get_param, add_custom_stat, add_custom_output

Group Configuration
-----------------------------

.. doxygenclass:: stat_bench::bench_impl::BenchmarkGroupRegister

.. doxygenclass:: stat_bench::PlotOption
