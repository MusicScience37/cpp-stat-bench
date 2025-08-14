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

#include <msgpack_light/output_stream.h>
#include <msgpack_light/serialize.h>

#include "stat_bench/reporter/msgpack_data_file_helper.h"  // IWYU pragma: keep
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/prepare_directory.h"

namespace stat_bench::reporter {

/*!
 * \brief Class of stream to write to file used in cpp-msgpack-light library.
 */
class MsgpackOutputFileStream : public msgpack_light::output_stream {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] file_path File path.
     */
    explicit MsgpackOutputFileStream(const std::string& file_path)
        : file_(std::fopen(file_path.c_str(), "wb")) {}

    MsgpackOutputFileStream(const MsgpackOutputFileStream&) = delete;
    MsgpackOutputFileStream(MsgpackOutputFileStream&&) = delete;
    auto operator=(const MsgpackOutputFileStream&)
        -> MsgpackOutputFileStream& = delete;
    auto operator=(MsgpackOutputFileStream&&)
        -> MsgpackOutputFileStream& = delete;

    /*!
     * \brief Destructor.
     */
    ~MsgpackOutputFileStream() { (void)std::fclose(file_); }

    /*!
     * \brief Write data.
     *
     * \param[in] data Pointer to the data.
     * \param[in] size Size of the data.
     */
    void write(const unsigned char* data, std::size_t size) override {
        if (std::fwrite(data, 1, size, file_) != size) {
            throw StatBenchException("Failed to write data.");
        }
    }

private:
    //! File descriptor.
    std::FILE* file_;
};

MsgPackReporter::MsgPackReporter(std::string file_path)
    : DataFileReporterBase(std::move(file_path)) {}

void MsgPackReporter::write_data_file(
    const std::string& file_path, const data_file_spec::RootData& data) {
    util::prepare_directory_for(file_path);

    MsgpackOutputFileStream stream{file_path};
    msgpack_light::serialize_to(stream, data);
}

}  // namespace stat_bench::reporter
