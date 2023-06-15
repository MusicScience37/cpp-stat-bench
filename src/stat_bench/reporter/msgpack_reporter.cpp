/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of MsgPackReporter class.
 */
#include "stat_bench/reporter/msgpack_reporter.h"

#include <cstdio>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <msgpack.hpp>
#include <msgpack/fbuffer.hpp>

#include "stat_bench/reporter/data_file_helper.h"
#include "stat_bench/reporter/msgpack_data_file_helper.h"  // IWYU pragma: keep
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/prepare_directory.h"

namespace stat_bench {
namespace reporter {

MsgPackReporter::MsgPackReporter(std::string file_path)
    : DataFileReporterBase(std::move(file_path)) {}

void MsgPackReporter::write_data_file(
    const std::string& file_path, const data_file_spec::RootData& data) {
    util::prepare_directory_for(file_path);

    std::FILE* file = std::fopen(file_path.c_str(), "wb");
    if (file == nullptr) {
        throw StatBenchException(
            fmt::format(FMT_STRING("Failed to open {}."), file_path));
    }

    msgpack::fbuffer buffer{file};
    msgpack::pack(buffer, data);

    (void)std::fclose(file);
}

}  // namespace reporter
}  // namespace stat_bench
