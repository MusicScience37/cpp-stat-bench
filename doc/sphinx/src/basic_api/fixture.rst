Writing Fixture
========================

Base Class of Fixture
-----------------------------

.. doxygenclass:: stat_bench::FixtureBase
    :members: setup, tear_down, add_param, add_threads_param, run
    :allow-dot-graphs:

.. doxygenclass:: stat_bench::bench_impl::IBenchmarkCase
    :members: none
    :allow-dot-graphs:

Classes Used with Fixtures
-------------------------------------

.. doxygenenum:: stat_bench::stat::CustomOutputAnalysisType

.. doxygenclass:: stat_bench::stat::CustomStatOutput
    :members: add

.. doxygenclass:: stat_bench::param::ParameterValueVector
    :members: add
    :allow-dot-graphs:

.. doxygenclass:: stat_bench::param::IParameterValueVector
    :members: none
    :allow-dot-graphs:
