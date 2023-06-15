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
 * \brief Definition of JsonReporter class.
 */
#pragma once

#include <exception>
#include <string>

#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/system_time_point.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/reporter/data_file_reporter_base.h"
#include "stat_bench/reporter/data_file_spec.h"
#include "stat_bench/reporter/i_reporter.h"

namespace stat_bench {
namespace reporter {

/*!
 * \brief Class to write JSON files.
 */
class JsonReporter final : public DataFileReporterBase {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] file_path File path.
     */
    explicit JsonReporter(std::string file_path);

    //! \copydoc stat_bench::reporter::DataFileReporterBase::write_data_file
    void write_data_file(const std::string& file_path,
        const data_file_spec::RootData& data) override;
};

}  // namespace reporter
}  // namespace stat_bench
