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
 * \brief Declaration of render_template function.
 */
#pragma once

#include <string>
#include <unordered_map>

namespace stat_bench {
namespace reporter {

/*!
 * \brief Render a template.
 *
 * \param[in] template_str Template string.
 * \param[in] params Parameters.
 * \return Rendering result.
 */
[[nodiscard]] auto render_template(std::string template_str,
    const std::unordered_map<std::string, std::string>& params) -> std::string;

}  // namespace reporter
}  // namespace stat_bench
