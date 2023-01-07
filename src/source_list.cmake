set(SOURCE_FILES
    stat_bench/bench_impl/benchmark_case_registry.cpp
    stat_bench/bench_impl/benchmark_group.cpp
    stat_bench/bench_impl/invocation_context_registry.cpp
    stat_bench/clock/monotone_clock_impl.cpp
    stat_bench/filters/composed_filter.cpp
    stat_bench/filters/regex_filter.cpp
    stat_bench/measurer/determine_iterations.cpp
    stat_bench/measurer/determine_warming_up_samples.cpp
    stat_bench/measurer/mean_processing_time_measurer.cpp
    stat_bench/measurer/measure_once.cpp
    stat_bench/measurer/processing_time_measurer.cpp
    stat_bench/param/parameter_generator.cpp
    stat_bench/reporter/cdf_line_plot_reporter.cpp
    stat_bench/reporter/console_reporter.cpp
    stat_bench/reporter/data_file_helper.cpp
    stat_bench/reporter/json_reporter.cpp
    stat_bench/reporter/render_template.cpp
    stat_bench/reporter/simple_line_plot_reporter.cpp
    stat_bench/reporter/violin_plot_reporter.cpp
    stat_bench/runner/command_line_parser.cpp
    stat_bench/runner/runner.cpp
    stat_bench/stat/calc_stat.cpp
    stat_bench/stat/statistics.cpp
    stat_bench/util/prepare_directory.cpp
    stat_bench/util/sync_barrier.cpp
    use_pointer.cpp
)
