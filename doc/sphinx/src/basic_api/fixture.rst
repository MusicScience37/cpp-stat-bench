Writing Fixture
========================

Base Class of Fixture
-----------------------------

.. doxygenclass:: stat_bench::FixtureBase
    :members: setup, tear_down, run

.. doxygenclass:: stat_bench::bench_impl::BenchmarkBase
    :members: add_param, add_threads_param

.. doxygenclass:: stat_bench::bench_impl::IBenchmarkCase
    :members: none

Classes Used with Fixtures
-------------------------------------

.. doxygenclass:: stat_bench::InvocationContext
    :members: threads, iterations, samples, get_param, add_custom_stat, add_custom_output

.. doxygenenum:: stat_bench::stat::CustomOutputAnalysisType

.. doxygenclass:: stat_bench::stat::CustomStatOutput
    :members: add

.. doxygenclass:: stat_bench::param::ParameterValueVector
    :members: add

.. doxygenclass:: stat_bench::param::IParameterValueVector
    :members: none
