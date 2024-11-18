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
 * \brief Definition of structs to specify the structure of data files.
 */
#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace reporter {
namespace data_file_spec {

/*!
 * \brief Struct of data of statistics.
 */
struct StatData {
    //! Mean.
    float mean{};

    //! Max.
    float max{};

    //! Min.
    float min{};

    //! Median.
    float median{};

    //! Variance.
    float variance{};

    //! Standard deviation.
    float standard_deviation{};

    //! Standard error.
    float standard_error{};
};

/*!
 * \brief Struct of durations.
 */
struct DurationData {
    //! Statistics.
    StatData stat{};

    //! Values.
    std::vector<std::vector<float>> values{};
};

/*!
 * \brief Struct of custom outputs with statistics.
 */
struct CustomStatOutputData {
    //! Name of data.
    util::Utf8String name{};

    //! Statistics.
    StatData stat{};

    //! Values.
    std::vector<std::vector<float>> values{};
};

/*!
 * \brief Struct of custom outputs without statistics.
 */
struct CustomOutputData {
    //! Name of data.
    util::Utf8String name{};

    //! Value.
    float value{};
};

/*!
 * \brief Struct of data in one case.
 */
struct MeasurementData {
    //! Name of group.
    util::Utf8String group_name{};

    //! Name of case.
    util::Utf8String case_name{};

    //! Parameters.
    std::unordered_map<util::Utf8String, util::Utf8String> params{};

    //! Name of measurer.
    util::Utf8String measurer_name{};

    //! Number of iterations.
    std::size_t iterations{};

    //! Number of samples.
    std::size_t samples{};

    //! Durations.
    DurationData durations{};

    //! Custom outputs with statistics.
    std::vector<CustomStatOutputData> custom_stat_outputs{};

    //! Custom outputs without statistics.
    std::vector<CustomOutputData> custom_outputs{};
};

/*!
 * \brief Struct of root objects in data files.
 */
struct RootData {
    //! Timestamp on beginning.
    util::Utf8String started_at{};

    //! Timestamp on end.
    util::Utf8String finished_at{};

    //! Measurements.
    std::vector<MeasurementData> measurements{};
};

}  // namespace data_file_spec
}  // namespace reporter
}  // namespace stat_bench
