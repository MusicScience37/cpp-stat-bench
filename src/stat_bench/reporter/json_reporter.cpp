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
 * \brief Implementation of JsonReporter class.
 */
#include "stat_bench/reporter/json_reporter.h"

#include <fstream>
#include <string_view>
#include <utility>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "data_file_schema_url.h"
#include "stat_bench/reporter/data_file_spec.h"
#include "stat_bench/reporter/json_data_file_helper.h"  // IWYU pragma: keep
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/prepare_directory.h"

namespace stat_bench {
namespace reporter {

JsonReporter::JsonReporter(std::string file_path)
    : DataFileReporterBase(std::move(file_path)) {}

void JsonReporter::write_data_file(
    const std::string& file_path, const data_file_spec::RootData& data) {
    util::prepare_directory_for(file_path);
    std::ofstream stream{file_path};
    if (!stream) {
        throw StatBenchException(
            fmt::format(FMT_STRING("Failed to open {}."), file_path));
    }

    auto json_data = nlohmann::json(data);
    json_data["$schema"] = data_file_schema_url;

    constexpr int indent = 2;
    constexpr char indent_char = ' ';
    constexpr bool ensure_ascii = true;
    stream << json_data.dump(indent, indent_char, ensure_ascii);
}

}  // namespace reporter
}  // namespace stat_bench
