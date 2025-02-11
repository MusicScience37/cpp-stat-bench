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
 * \brief Definition of data_file_schema_url constant.
 */
#pragma once

#include <string_view>

namespace stat_bench {
namespace reporter {

//! URL of the schema of data files.
inline constexpr std::string_view data_file_schema_url =
    "https://cppstatbench.musicscience37.com/schemas/data_file_schema_v3.json";

}  // namespace reporter
}  // namespace stat_bench
