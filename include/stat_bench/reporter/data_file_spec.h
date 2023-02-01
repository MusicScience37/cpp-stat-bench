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
#include <string>
#include <unordered_map>
#include <vector>

namespace stat_bench {
namespace reporter {
namespace data_file_spec {

/*!
 * \brief Struct of data of statistics.
 */
struct StatData {
    //! Mean.
    double mean{};

    //! Max.
    double max{};

    //! Min.
    double min{};

    //! Variance.
    double variance{};

    //! Standard deviation.
    double standard_deviation{};
};

/*!
 * \brief Struct of durations.
 */
struct DurationData {
    //! Statistics.
    StatData stat{};

    //! Values.
    std::vector<std::vector<double>> values{};
};

/*!
 * \brief Struct of custom outputs with statistics.
 */
struct CustomStatOutputData {
    //! Name of data.
    std::string name{};

    //! Statistics.
    StatData stat{};

    //! Values.
    std::vector<std::vector<double>> values{};
};

/*!
 * \brief Struct of custom outputs without statistics.
 */
struct CustomOutputData {
    //! Name of data.
    std::string name{};

    //! Value.
    double value{};
};

/*!
 * \brief Struct of data in one case.
 */
struct MeasurementData {
    //! Name of group.
    std::string group_name{};

    //! Name of case.
    std::string case_name{};

    //! Parameters.
    std::unordered_map<std::string, std::string> params{};

    //! Name of measurer.
    std::string measurer_name{};

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
    std::string started_at{};

    //! Timestamp on end.
    std::string finished_at{};

    //! Measurements.
    std::vector<MeasurementData> measurements{};
};

}  // namespace data_file_spec
}  // namespace reporter
}  // namespace stat_bench
