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
 * \brief Declaration of check_glob_pattern function.
 */
#pragma once

#include "stat_bench/util/string_view.h"

namespace stat_bench {
namespace util {

/*!
 * \brief Check whether a string matches with a glob pattern.
 *
 * \param[in] pattern Glob pattern.
 * \param[in] str String.
 * \retval true The input string matches with the glob pattern.
 * \retval false The input string doesn't match with the glob pattern.
 */
[[nodiscard]] auto check_glob_pattern(
    StringView pattern, StringView str) -> bool;

}  // namespace util
}  // namespace stat_bench
