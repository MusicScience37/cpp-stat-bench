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

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

#include <lyra/args.hpp>
#include <lyra/opt.hpp>
#include <lyra/parser.hpp>

namespace stat_bench {
namespace runner {

CommandLineParser::CommandLineParser() {
    cli_.add_argument(lyra::opt(config_.show_help)
            .name("-h")
            .name("--help")
            .optional()
            .help("Show this help."));

    cli_.add_argument(lyra::opt(config_.plot_prefix, "prefix")
            .name("--plot")
            .optional()
            .help("Generate plots of results."));

    cli_.add_argument(lyra::opt(config_.json_file_path, "filepath")
            .name("--json")
            .optional()
            .help("Generate JSON data file of results."));

    cli_.add_argument(lyra::opt(config_.msgpack_file_path, "filepath")
            .name("--msgpack")
            .optional()
            .help("Generate MsgPack data file of results."));

    cli_.add_argument(
        lyra::opt(config_.compressed_msgpack_file_path, "filepath")
            .name("--compressed-msgpack")
            .optional()
            .help("Generate compressed MsgPack data file of results."));

    cli_.add_argument(lyra::opt(config_.samples, "num")
            .name("--samples")
            .optional()
            .choices([](std::size_t val) { return val > 0; })
            .help("Number of samples for measurements of processing time."));

    cli_.add_argument(lyra::opt(config_.min_sample_duration_sec, "num")
            .name("--min_sample_duration")
            .optional()
            .choices([](double val) { return val > 0.0; })
            .help("Minimum duration of a sample for measurement "
                  "of mean processing time. [sec]"));

    cli_.add_argument(lyra::opt(config_.min_warming_up_iterations, "num")
            .name("--min_warming_up_iterations")
            .optional()
            .help("Minimum number of iterations for warming up."));

    cli_.add_argument(lyra::opt(config_.min_warming_up_duration_sec, "num")
            .name("--min_warming_up_duration_sec")
            .optional()
            .choices([](double val) { return val >= 0.0; })
            .help("Minimum duration for warming up. [sec]"));

    cli_.add_argument(lyra::opt(config_.include_glob, "pattern")
            .name("--include")
            .cardinality(0, 0)
            .help("Specify glob patterns of benchmark names to include. "
                  "When omitted, this option won't filter any benchmarks."));

    cli_.add_argument(lyra::opt(config_.exclude_glob, "pattern")
            .name("--exclude")
            .cardinality(0, 0)
            .help("Specify glob patterns of benchmark names to exclude. "
                  "When omitted, this option won't filter any benchmarks."));

    cli_.add_argument(lyra::opt(config_.include_regex, "regex")
            .name("--include_regex")
            .cardinality(0, 0)
            .help("Specify regular expressions of benchmark names to include. "
                  "When omitted, this option won't filter any benchmarks."));

    cli_.add_argument(lyra::opt(config_.exclude_regex, "regex")
            .name("--exclude_regex")
            .cardinality(0, 0)
            .help("Specify regular expressions of benchmark names to exclude. "
                  "When omitted, this option won't filter any benchmarks."));
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
