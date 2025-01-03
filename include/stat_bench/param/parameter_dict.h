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

// IWYU pragma: no_include <string>

#include <functional>
#include <unordered_map>

#include <fmt/base.h>
#include <fmt/format.h>

#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/utf8_string.h"

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
    explicit ParameterDict(
        std::unordered_map<ParameterName, ParameterValue> data);

    /*!
     * \brief Check whether this is empty.
     *
     * \retval true This has no parameter.
     * \retval false This has one or more parameters.
     */
    [[nodiscard]] auto empty() const noexcept -> bool;

    /*!
     * \brief Check whether this has a parameter with a name.
     *
     * \param[in] param_name Parameter name to check.
     * \retval true This has a parameter with the given name.
     * \retval false This doesn't have a parameter with the given name.
     */
    [[nodiscard]] auto has(const ParameterName& param_name) const -> bool;

    /*!
     * \brief Get a parameter value.
     *
     * \tparam T Type of the value.
     * \param[in] param_name Parameter name.
     * \return Value.
     */
    template <typename T>
    [[nodiscard]] auto get(const ParameterName& param_name) const -> const T& {
        const auto iter = data_.find(param_name);
        if (iter == data_.end()) {
            throw StatBenchException(
                fmt::format("Parameter {} not found.", param_name));
        }
        return iter->second.as<T>();
    }

    /*!
     * \brief Get a parameter value as double.
     *
     * \param[in] param_name Parameter name.
     * \return Value.
     */
    [[nodiscard]] auto get_as_double(const ParameterName& param_name) const
        -> double;

    /*!
     * \brief Format to string.
     *
     * \param[in] out Output iterator to write the formatted string.
     * \return Output iterator after formatting.
     */
    [[nodiscard]] auto format_to(fmt::format_context::iterator out) const
        -> fmt::format_context::iterator;

    /*!
     * \brief Get as a dictionary of string values.
     *
     * \return Dictionary.
     */
    [[nodiscard]] auto as_string_dict() const
        -> std::unordered_map<util::Utf8String, util::Utf8String>;

    /*!
     * \brief Calculate hash value.
     *
     * \return Hash value.
     */
    [[nodiscard]] auto calculate_hash() const -> std::size_t;

    /*!
     * \brief Check whether this is equal to another dictionary.
     *
     * \param[in] rhs Right-hand-side dictionary.
     * \retval true This is equal to the right-hand-side dictionary.
     * \retval false This is not equal to the right-hand-side dictionary.
     */
    [[nodiscard]] auto operator==(const ParameterDict& rhs) const -> bool;

    /*!
     * \brief Check whether this is not equal to another dictionary.
     *
     * \param[in] rhs Right-hand-side dictionary.
     * \retval true This is not equal to the right-hand-side dictionary.
     * \retval false This is equal to the right-hand-side dictionary.
     */
    [[nodiscard]] auto operator!=(const ParameterDict& rhs) const -> bool;

private:
    //! Data.
    std::unordered_map<ParameterName, ParameterValue> data_;
};

}  // namespace param
}  // namespace stat_bench

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for
 * stat_bench::param::ParameterDict
 */
template <>
struct formatter<stat_bench::param::ParameterDict>
    : public formatter<string_view> {
    /*!
     * \brief Format.
     *
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    auto format(const stat_bench::param::ParameterDict& val,
        format_context& context) const -> typename format_context::iterator;
};

}  // namespace fmt

namespace std {

/*!
 * \brief Implementation of std::hash for stat_bench::param::ParameterDict.
 */
template <>
class hash<stat_bench::param::ParameterDict> {
public:
    /*!
     * \brief Operator.
     *
     * \param[in] dict Dictionary.
     * \return Hash value.
     */
    auto operator()(const stat_bench::param::ParameterDict& dict) const
        -> std::size_t {
        return dict.calculate_hash();
    }
};

}  // namespace std
