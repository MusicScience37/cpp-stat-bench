/*
 * Copyright 2024 MusicScience37 (Kenta Kabashima)
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
 * \brief Definition of num_threads_parameter_name function.
 */
#pragma once

#include <string>

#include "stat_bench/param/parameter_name.h"

namespace stat_bench::param {

/*!
 * \brief Get the parameter name for the number of threads.
 *
 * \return Parameter name.
 */
inline auto num_threads_parameter_name() -> const ParameterName& {
    static auto name = ParameterName("threads");
    return name;
}

}  // namespace stat_bench::param
