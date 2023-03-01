set(SOURCE_FILES
    stat_bench/bench_impl/benchmark_case_registry_test.cpp
    stat_bench/bench_impl/benchmark_group_test.cpp
    stat_bench/bench_impl/threadable_invoker_test.cpp
    stat_bench/benchmark_condition_test.cpp
    stat_bench/benchmark_full_name_test.cpp
    stat_bench/clock/duration_test.cpp
    stat_bench/clock/monotone_clock_impl_test.cpp
    stat_bench/clock/monotone_clock_test.cpp
    stat_bench/clock/monotone_time_point_test.cpp
    stat_bench/clock/stop_watch_test.cpp
    stat_bench/clock/system_clock_test.cpp
    stat_bench/do_not_optimize_test.cpp
    stat_bench/filters/composed_filter_test.cpp
    stat_bench/filters/regex_filter_test.cpp
    stat_bench/fixture_base_test.cpp
    stat_bench/invocation_context_test.cpp
    stat_bench/measurer/mean_processing_time_measurer_test.cpp
    stat_bench/measurer/measurement_test.cpp
    stat_bench/measurer/processing_time_measurer_test.cpp
    stat_bench/memory_barrier_test.cpp
    stat_bench/param/parameter_config_test.cpp
    stat_bench/param/parameter_dict_test.cpp
    stat_bench/param/parameter_generator_test.cpp
    stat_bench/param/parameter_value_test.cpp
    stat_bench/param/parameter_value_vector_test.cpp
    stat_bench/reporter/cdf_line_plot_reporter_test.cpp
    stat_bench/reporter/console_reporter_test.cpp
    stat_bench/reporter/json_data_file_helper_test.cpp
    stat_bench/reporter/json_reporter_test.cpp
    stat_bench/reporter/simple_line_plot_reporter_test.cpp
    stat_bench/reporter/violin_plot_reporter_test.cpp
    stat_bench/runner/command_line_parser_test.cpp
    stat_bench/runner/runner_test.cpp
    stat_bench/stat/calc_stat_test.cpp
    stat_bench/stat/custom_stat_output_test.cpp
    stat_bench/stat/statistics_test.cpp
    stat_bench/util/check_glob_pattern_test.cpp
    stat_bench/util/prepare_directory_test.cpp
    stat_bench/util/sync_barrier_test.cpp
    test_main.cpp
)
