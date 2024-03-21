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
 * \brief Implementation of CompressedMsgPackReporter class.
 */
#include "stat_bench/reporter/compressed_msgpack_reporter.h"

#include <cstdio>
#include <utility>

#include <fmt/core.h>
#include <fmt/format.h>
#include <msgpack_light/output_stream.h>
#include <msgpack_light/serialize.h>
#include <zlib.h>

#include "stat_bench/reporter/msgpack_data_file_helper.h"  // IWYU pragma: keep
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/prepare_directory.h"

namespace stat_bench {
namespace reporter {

/*!
 * \brief Class of buffers to write compressed files in msgpack library.
 */
class CompressedMsgpackOutputFileStream : public msgpack_light::output_stream {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] file_path File path.
     */
    explicit CompressedMsgpackOutputFileStream(const std::string& file_path)
        : file_(gzopen(file_path.c_str(), "wb9")) {
        if (file_ == nullptr) {
            throw StatBenchException(
                fmt::format(FMT_STRING("Failed to open {}."), file_path));
        }
    }

    CompressedMsgpackOutputFileStream(
        const CompressedMsgpackOutputFileStream&) = delete;
    CompressedMsgpackOutputFileStream(
        CompressedMsgpackOutputFileStream&&) = delete;
    auto operator=(const CompressedMsgpackOutputFileStream&)
        -> CompressedMsgpackOutputFileStream& = delete;
    auto operator=(CompressedMsgpackOutputFileStream&&)
        -> CompressedMsgpackOutputFileStream& = delete;

    /*!
     * \brief Destructor.
     */
    ~CompressedMsgpackOutputFileStream() { (void)gzclose(file_); }

    /*!
     * \brief Write data.
     *
     * \param[in] data Pointer to the data.
     * \param[in] size Size of the data.
     */
    void write(const unsigned char* data, std::size_t size) override {
        if (gzwrite(file_, data, size) != size) {
            throw StatBenchException("Failed to write data.");
        }
    }

private:
    //! File.
    gzFile file_;
};

CompressedMsgPackReporter::CompressedMsgPackReporter(std::string file_path)
    : DataFileReporterBase(std::move(file_path)) {}

void CompressedMsgPackReporter::write_data_file(
    const std::string& file_path, const data_file_spec::RootData& data) {
    util::prepare_directory_for(file_path);

    CompressedMsgpackOutputFileStream stream{file_path};
    msgpack_light::serialize_to(stream, data);
}

}  // namespace reporter
}  // namespace stat_bench
