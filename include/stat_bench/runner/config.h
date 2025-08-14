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
 * \brief Definition of Runner class.
 */
#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace stat_bench::runner {

namespace impl {

//! Default number of samples for measurements of processing time.
static constexpr std::size_t default_samples = 30;

/*!
 * \brief Default minimum duration of a sample for measurement of mean
 * processing time. [sec]
 */
static constexpr double default_min_sample_duration_sec = 0.03;

//! Default minimum number of iterations for warming up.
static constexpr std::size_t default_min_warming_up_iterations = 1;

//! Default minimum duration for warming up. [sec]
static constexpr double default_min_warming_up_duration_sec = 0.03;

}  // namespace impl

/*!
 * \brief Class of configurations.
 */
struct Config {
    //! Whether to show help.
    bool show_help{false};

    //! Number of samples for measurements of processing time.
    std::size_t samples{impl::default_samples};

    /*!
     * \brief Minimum duration of a sample for measurement of mean processing
     * time. [sec]
     */
    double min_sample_duration_sec{impl::default_min_sample_duration_sec};

    //! Minimum number of iterations for warming up.
    std::size_t min_warming_up_iterations{
        impl::default_min_warming_up_iterations};

    //! Minimum duration for warming up. [sec]
    double min_warming_up_duration_sec{
        impl::default_min_warming_up_duration_sec};

    /*!
     * \brief Prefix of filepaths to generate plots.
     *
     * Empty string specifies no output.
     */
    std::string plot_prefix{};

    /*!
     * \brief File path of JSON data file.
     *
     * Empty string specifies no output.
     */
    std::string json_file_path{};

    /*!
     * \brief File path of MsgPack data file.
     *
     * Empty string specifies no output.
     */
    std::string msgpack_file_path{};

    /*!
     * \brief File path of compressed MsgPack data file.
     *
     * Empty string specifies no output.
     */
    std::string compressed_msgpack_file_path{};

    //! Glob patterns of benchmark names to include.
    std::vector<std::string> include_glob{};

    //! Glob patterns of benchmark names to exclude.
    std::vector<std::string> exclude_glob{};

    //! Regular expressions of benchmark names to include.
    std::vector<std::string> include_regex{};

    //! Regular expressions of benchmark names to exclude.
    std::vector<std::string> exclude_regex{};
};

}  // namespace stat_bench::runner
