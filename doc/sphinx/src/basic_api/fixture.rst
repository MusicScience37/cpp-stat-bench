Writing Fixture
========================

Base Class of Fixture
-----------------------------

.. doxygenclass:: stat_bench::FixtureBase
    :members: setup, tear_down, add_param, add_threads_param, run

.. doxygenclass:: stat_bench::bench_impl::IBenchmarkCase
    :members: none

Classes Used with Fixtures
-------------------------------------

.. doxygenenum:: stat_bench::stat::CustomOutputAnalysisType

.. doxygenclass:: stat_bench::stat::CustomStatOutput
    :members: add

.. doxygenclass:: stat_bench::param::ParameterValueVector
    :members: add

.. doxygenclass:: stat_bench::param::IParameterValueVector
    :members: none
