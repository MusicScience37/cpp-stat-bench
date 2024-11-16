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
 * \brief Definition of ParameterGenerator class.
 */
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value_vector.h"

namespace stat_bench {
namespace param {

/*!
 * \brief Class of generators of parameter dictionaries.
 */
class ParameterGenerator {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] params Parameters. (Pairs of names and vectors of values.)
     */
    explicit ParameterGenerator(const std::vector<std::pair<ParameterName,
            std::shared_ptr<IParameterValueVector>>>& params);

    /*!
     * \brief Iterate once.
     *
     * \return Whether the next parameters exists.
     */
    [[nodiscard]] auto iterate() -> bool;

    /*!
     * \brief Generate the parameters.
     *
     * \return Parameters.
     */
    [[nodiscard]] auto generate() const -> ParameterDict;

private:
    /*!
     * \brief Struct of data per parameter.
     */
    struct ParamData {
        //! Name.
        ParameterName name{""};

        //! Values.
        std::shared_ptr<IParameterValueVector> values{};

        //! Next iterator.
        IParameterValueVector::ConstIterator next{};

        //! Beginning iterator.
        IParameterValueVector::ConstIterator begin{};

        //! Past-the-end iterator.
        IParameterValueVector::ConstIterator end{};
    };

    //! Parameters.
    std::vector<ParamData> params_{};
};

}  // namespace param
}  // namespace stat_bench
