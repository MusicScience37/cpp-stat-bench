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
 * \brief Definition of CommandLineParser class.
 */
#pragma once

// Following is required for build using GCC.
#include <lyra/lyra.hpp>  // IWYU pragma: keep
// IWYU pragma: no_include <lyra/cli.hpp>

#include "stat_bench/runner/config.h"

namespace stat_bench::runner {

/*!
 * \brief Class to parse command line arguments.
 */
class CommandLineParser {
public:
    /*!
     * \brief Constructor.
     */
    CommandLineParser();

    CommandLineParser(const CommandLineParser&) = delete;
    CommandLineParser(CommandLineParser&&) = delete;
    auto operator=(const CommandLineParser&) -> CommandLineParser& = delete;
    auto operator=(CommandLineParser&&) -> CommandLineParser& = delete;

    /*!
     * \brief Destructor.
     */
    ~CommandLineParser();

    /*!
     * \brief Parse command line arguments.
     *
     * \param[in] argc Number of arguments.
     * \param[in] argv Arguments.
     */
    void parse_cli(int argc, const char** argv);

    /*!
     * \brief Access to the command line interface definition.
     *
     * \note For usage of `lyra::cli` objects, see [Lyra
     * documentation](https://www.bfgroup.xyz/Lyra/).
     *
     * \return Reference to the definition.
     */
    [[nodiscard]] auto cli() -> lyra::cli& { return cli_; }

    /*!
     * \brief Get the configuration.
     *
     * \return Configuration.
     */
    [[nodiscard]] auto config() -> const Config& { return config_; }

private:
    //! Configurations.
    Config config_{};

    //! Command line interface.
    lyra::cli cli_{};
};

}  // namespace stat_bench::runner
