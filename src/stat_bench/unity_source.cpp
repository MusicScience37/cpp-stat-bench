#include "bench_impl/benchmark_case_registry.cpp"  // NOLINT(bugprone-suspicious-include)
#include "bench_impl/benchmark_group.cpp"  // NOLINT(bugprone-suspicious-include)
#include "bench_impl/invocation_context_registry.cpp"  // NOLINT(bugprone-suspicious-include)
#include "benchmark_case_name.cpp"        // NOLINT(bugprone-suspicious-include)
#include "benchmark_full_name.cpp"        // NOLINT(bugprone-suspicious-include)
#include "benchmark_group_name.cpp"       // NOLINT(bugprone-suspicious-include)
#include "clock/monotone_time_point.cpp"  // NOLINT(bugprone-suspicious-include)
#include "clock/system_time_point.cpp"    // NOLINT(bugprone-suspicious-include)
#include "custom_output_name.cpp"         // NOLINT(bugprone-suspicious-include)
#include "filters/composed_filter.cpp"    // NOLINT(bugprone-suspicious-include)
#include "filters/glob_filter.cpp"        // NOLINT(bugprone-suspicious-include)
#include "filters/regex_filter.cpp"       // NOLINT(bugprone-suspicious-include)
#include "measurer/determine_iterations.cpp"  // NOLINT(bugprone-suspicious-include)
#include "measurer/determine_warming_up_samples.cpp"  // NOLINT(bugprone-suspicious-include)
#include "measurer/mean_processing_time_measurer.cpp"  // NOLINT(bugprone-suspicious-include)
#include "measurer/measure_once.cpp"   // NOLINT(bugprone-suspicious-include)
#include "measurer/measurer_name.cpp"  // NOLINT(bugprone-suspicious-include)
#include "measurer/processing_time_measurer.cpp"  // NOLINT(bugprone-suspicious-include)
#include "param/parameter_dict.cpp"       // NOLINT(bugprone-suspicious-include)
#include "param/parameter_generator.cpp"  // NOLINT(bugprone-suspicious-include)
#include "param/parameter_name.cpp"       // NOLINT(bugprone-suspicious-include)
#include "plots/jinja_renderer.cpp"       // NOLINT(bugprone-suspicious-include)
#include "reporter/cdf_line_plot_reporter.cpp"  // NOLINT(bugprone-suspicious-include)
#include "reporter/compressed_msgpack_reporter.cpp"  // NOLINT(bugprone-suspicious-include)
#include "reporter/console_reporter.cpp"  // NOLINT(bugprone-suspicious-include)
#include "reporter/data_file_helper.cpp"  // NOLINT(bugprone-suspicious-include)
#include "reporter/data_file_reporter_base.cpp"  // NOLINT(bugprone-suspicious-include)
#include "reporter/json_reporter.cpp"     // NOLINT(bugprone-suspicious-include)
#include "reporter/msgpack_reporter.cpp"  // NOLINT(bugprone-suspicious-include)
#include "reporter/simple_line_plot_reporter.cpp"  // NOLINT(bugprone-suspicious-include)
#include "reporter/violin_plot_reporter.cpp"  // NOLINT(bugprone-suspicious-include)
#include "runner/command_line_parser.cpp"  // NOLINT(bugprone-suspicious-include)
#include "runner/runner.cpp"            // NOLINT(bugprone-suspicious-include)
#include "stat/calc_stat.cpp"           // NOLINT(bugprone-suspicious-include)
#include "use_pointer.cpp"              // NOLINT(bugprone-suspicious-include)
#include "util/check_glob_pattern.cpp"  // NOLINT(bugprone-suspicious-include)
#include "util/escape_for_html.cpp"     // NOLINT(bugprone-suspicious-include)
#include "util/prepare_directory.cpp"   // NOLINT(bugprone-suspicious-include)
#include "util/sync_barrier.cpp"        // NOLINT(bugprone-suspicious-include)
#include "util/utf8_string.cpp"         // NOLINT(bugprone-suspicious-include)
