set(SOURCE_FILES
    bench_impl/benchmark_case_registry.cpp
    bench_impl/benchmark_group.cpp
    bench_impl/invocation_context_registry.cpp
    benchmark_case_name.cpp
    benchmark_full_name.cpp
    benchmark_group_name.cpp
    clock/monotone_time_point.cpp
    clock/system_time_point.cpp
    custom_output_name.cpp
    filters/composed_filter.cpp
    filters/glob_filter.cpp
    filters/regex_filter.cpp
    measurer/determine_iterations.cpp
    measurer/determine_warming_up_samples.cpp
    measurer/mean_processing_time_measurer.cpp
    measurer/measure_once.cpp
    measurer/measurer_name.cpp
    measurer/processing_time_measurer.cpp
    param/parameter_dict.cpp
    param/parameter_generator.cpp
    param/parameter_name.cpp
    plots/cdf_line_plot.cpp
    plots/jinja_renderer.cpp
    plots/plotly_plotter.cpp
    plots/samples_line_plot.cpp
    plots/violin_plot.cpp
    reporter/cdf_line_plot_reporter.cpp
    reporter/compressed_msgpack_reporter.cpp
    reporter/console_reporter.cpp
    reporter/data_file_helper.cpp
    reporter/data_file_reporter_base.cpp
    reporter/json_reporter.cpp
    reporter/msgpack_reporter.cpp
    reporter/plot_reporter.cpp
    reporter/simple_line_plot_reporter.cpp
    reporter/violin_plot_reporter.cpp
    runner/command_line_parser.cpp
    runner/runner.cpp
    stat/calc_stat.cpp
    use_pointer.cpp
    util/check_glob_pattern.cpp
    util/escape_for_html.cpp
    util/prepare_directory.cpp
    util/sync_barrier.cpp
    util/utf8_string.cpp
)
