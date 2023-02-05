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
 * \brief Definition of create_ordinary_parameter_dict function.
 */
#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_value.h"

namespace stat_bench_test {
namespace param {

/*!
 * \brief Create an ordinary parameter dictionary.
 *
 * \return Parameter dictionary.
 */
[[nodiscard]] inline auto create_ordinary_parameter_dict()
    -> stat_bench::param::ParameterDict {
    std::unordered_map<std::string, stat_bench::param::ParameterValue> data;
    data.emplace(
        "threads", stat_bench::param::ParameterValue().emplace<std::size_t>(1));
    return stat_bench::param::ParameterDict(data);
}

}  // namespace param
}  // namespace stat_bench_test
