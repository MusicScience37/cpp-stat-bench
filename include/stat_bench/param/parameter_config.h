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
 * \brief Definition of ParameterConfig class.
 */
#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "stat_bench/param/parameter_generator.h"
#include "stat_bench/param/parameter_value_vector.h"

namespace stat_bench {
namespace param {

/*!
 * \brief Class of configurations of parameters.
 */
class ParameterConfig {
public:
    /*!
     * \brief Constructor.
     */
    ParameterConfig() = default;

    /*!
     * \brief Add a parameter.
     *
     * \tparam T Type of parameter values.
     * \param[in] param_name Parameter name.
     * \return Vector of parameter values.
     */
    template <typename T>
    [[nodiscard]] auto add(const std::string& param_name)
        -> std::shared_ptr<ParameterValueVector<T>> {
        auto vec = std::make_shared<ParameterValueVector<T>>();
        params_.emplace_back(param_name, vec);
        return vec;
    }

    /*!
     * \brief Check whether a parameter exists.
     *
     * \param[in] param_name Parameter name.
     * \return Whether the parameter with the given name exists.
     */
    [[nodiscard]] auto has(const std::string& param_name) const -> bool {
        return std::find_if(params_.begin(), params_.end(),
                   [&param_name](const std::pair<std::string,
                       std::shared_ptr<IParameterValueVector>>& pair) {
                       return pair.first == param_name;
                   }) != params_.end();
    }

    /*!
     * \brief Create a generator of parameter dictionaries.
     *
     * \return Generator.
     */
    [[nodiscard]] auto create_generator() const {
        return ParameterGenerator(params_);
    }

private:
    //! Parameters.
    std::vector<std::pair<std::string, std::shared_ptr<IParameterValueVector>>>
        params_{};
};

}  // namespace param
}  // namespace stat_bench
