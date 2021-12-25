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
 * \brief Definition of ParameterDict class.
 */
#pragma once

#include <string>
#include <unordered_map>

#include "stat_bench/param/parameter_value.h"
#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace param {

/*!
 * \brief Class of dictionaries of parameters.
 */
class ParameterDict {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     */
    explicit ParameterDict(std::unordered_map<std::string, ParameterValue> data)
        : data_(std::move(data)) {}

    /*!
     * \brief Get a parameter value.
     *
     * \tparam T Type of the value.
     * \param[in] param_name Parameter name.
     * \return Value.
     */
    template <typename T>
    [[nodiscard]] auto get(const std::string& param_name) const -> const T& {
        const auto iter = data_.find(param_name);
        if (iter == data_.end()) {
            throw StatBenchException(
                fmt::format("Parameter {} not found.", param_name));
        }
        return iter->second.as<T>();
    }

private:
    //! Data.
    std::unordered_map<std::string, ParameterValue> data_;
};

}  // namespace param
}  // namespace stat_bench
