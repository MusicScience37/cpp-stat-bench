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
 * \brief Declaration of escape_for_html function.
 */
#pragma once

#include <string>

#include "stat_bench/util/string_view.h"

namespace stat_bench {
namespace util {

/*!
 * \brief Escape a string for HTML.
 *
 * \param[in] input Input string.
 * \return Escaped string.
 */
[[nodiscard]] auto escape_for_html(const StringView& input) -> std::string;

}  // namespace util
}  // namespace stat_bench
