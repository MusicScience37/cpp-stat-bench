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
 * \brief Definition of BenchmarkGroupName class.
 */
#pragma once

#include <cstddef>
#include <functional>
#include <ostream>
#include <string>
#include <utility>

#include <fmt/base.h>

#include "stat_bench/util/utf8_string.h"

namespace stat_bench {

/*!
 * \brief Class of names of groups of benchmarks.
 */
class BenchmarkGroupName {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] str String of the name.
     */
    explicit BenchmarkGroupName(util::Utf8String str) noexcept;

    /*!
     * \brief Constructor.
     *
     * \param[in] str String of the name.
     */
    explicit BenchmarkGroupName(std::string str)
        : BenchmarkGroupName(util::Utf8String(std::move(str))) {}

    /*!
     * \brief Get the string of the name.
     *
     * \return String of the name.
     */
    [[nodiscard]] auto str() const noexcept -> const util::Utf8String&;

private:
    //! String of the name.
    util::Utf8String str_;
};

/*!
 * \brief Compare two BenchmarkGroupName objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The two objects are equal.
 * \retval false The two objects are not equal.
 */
[[nodiscard]] inline auto operator==(const BenchmarkGroupName& lhs,
    const BenchmarkGroupName& rhs) noexcept -> bool {
    return lhs.str() == rhs.str();
}

/*!
 * \brief Compare two BenchmarkGroupName objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The two objects are not equal.
 * \retval false The two objects are equal.
 */
[[nodiscard]] inline auto operator!=(const BenchmarkGroupName& lhs,
    const BenchmarkGroupName& rhs) noexcept -> bool {
    return !(lhs == rhs);
}

}  // namespace stat_bench

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for stat_bench::BenchmarkGroupName.
 */
template <>
struct formatter<stat_bench::BenchmarkGroupName>
    : public formatter<stat_bench::util::Utf8String> {
    /*!
     * \brief Format.
     *
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    auto format(const stat_bench::BenchmarkGroupName& val,
        fmt::format_context& context) const -> fmt::format_context::iterator {
        return formatter<stat_bench::util::Utf8String>::format(
            val.str(), context);
    }
};

}  // namespace fmt

namespace stat_bench {

/*!
 * \brief Format to a stream.
 *
 * \param[in,out] stream Stream.
 * \param[in] val Value.
 * \return Stream.
 */
inline auto operator<<(std::ostream& stream, const BenchmarkGroupName& val)
    -> std::ostream& {
    return stream << val.str();
}

}  // namespace stat_bench

namespace std {

/*!
 * \brief Implementation of std::hash for stat_bench::BenchmarkGroupName.
 */
template <>
class hash<stat_bench::BenchmarkGroupName> {
public:
    /*!
     * \brief Hash function.
     *
     * \param[in] val Value.
     * \return Hash value.
     */
    auto operator()(const stat_bench::BenchmarkGroupName& val) const
        -> std::size_t {
        return hash_(val.str());
    }

private:
    //! Hash function for strings.
    std::hash<stat_bench::util::Utf8String> hash_;
};

}  // namespace std
