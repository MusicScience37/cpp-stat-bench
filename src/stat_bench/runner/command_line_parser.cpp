/*
 * Copyright 2021 MusicScience37 (Kenta Kabashima)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * \file
 * \brief Implementation of CommandLineParser class.
 */
#include "stat_bench/runner/command_line_parser.h"

namespace stat_bench {
namespace runner {

CommandLineParser::CommandLineParser() {
    cli_ |= lyra::opt(config_.show_help)["-h"]["--help"]("Show this help.");

    cli_ |= lyra::opt(config_.plot_prefix, "prefix")["--plot"](
        "Generate plots of results.");

    cli_ |= lyra::opt(config_.json_file_path, "filepath")["--json"](
        "Generate JSON data file.");

    cli_ |= lyra::opt(config_.processing_time_samples, "num")["--samples"](
        "Number of samples for measurements of processing time.")
                .choices([](std::size_t val) { return val > 0; });

    cli_ |= lyra::opt(
        config_.mean_processing_time_samples, "num")["--mean_samples"](
        "Number of samples for measurements of mean processing time.")
                .choices([](std::size_t val) { return val > 0; });

    cli_ |= lyra::opt(
        config_.min_sample_duration_sec, "num")["--min_sample_duration"](
        "Minimum duration of a sample for measurement of mean processing time. "
        "[sec]")
                .choices([](double val) { return val > 0.0; });

    cli_ |= lyra::opt(config_.min_warming_up_iterations,
        "num")["--min_warming_up_iterations"](
        "Minimum number of iterations for warming up.");

    cli_ |= lyra::opt(config_.min_warming_up_duration_sec,
        "num")["--min_warming_up_duration_sec"](
        "Minimum duration for warming up. [sec]")
                .choices([](double val) { return val >= 0.0; });
}

CommandLineParser::~CommandLineParser() = default;

void CommandLineParser::parse_cli(int argc, const char** argv) {
    const auto result = cli_.parse(lyra::args{argc, argv});
    if (!result) {
        throw std::runtime_error(result.message());
    }
}

}  // namespace runner
}  // namespace stat_bench
