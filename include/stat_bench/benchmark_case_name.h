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
 * \brief Definition of BenchmarkCaseName class.
 */
#pragma once

#include <fmt/core.h>
#include <fmt/format.h>

#include "stat_bench/util/utf8_string.h"

namespace stat_bench {

/*!
 * \brief Class of names of cases of benchmarks.
 */
class BenchmarkCaseName {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] str String of the name.
     */
    explicit BenchmarkCaseName(util::Utf8String str) noexcept;

    /*!
     * \brief Constructor.
     *
     * \param[in] str String of the name.
     */
    explicit BenchmarkCaseName(const std::string& str)
        : BenchmarkCaseName(util::Utf8String(str)) {}

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
 * \brief Compare two BenchmarkCaseName objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The two objects are equal.
 * \retval false The two objects are not equal.
 */
[[nodiscard]] inline auto operator==(const BenchmarkCaseName& lhs,
    const BenchmarkCaseName& rhs) noexcept -> bool {
    return lhs.str() == rhs.str();
}

/*!
 * \brief Compare two BenchmarkCaseName objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The two objects are not equal.
 * \retval false The two objects are equal.
 */
[[nodiscard]] inline auto operator!=(const BenchmarkCaseName& lhs,
    const BenchmarkCaseName& rhs) noexcept -> bool {
    return !(lhs == rhs);
}

}  // namespace stat_bench

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for stat_bench::BenchmarkCaseName.
 */
template <>
struct formatter<stat_bench::BenchmarkCaseName>
    : public formatter<std::string> {
    /*!
     * \brief Format.
     *
     * \tparam FormatContext Type of the context.
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    auto format(const stat_bench::BenchmarkCaseName& val,
        fmt::format_context& context) const -> fmt::format_context::iterator {
        return formatter<std::string>::format(val.str().str(), context);
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
inline auto operator<<(std::ostream& stream, const BenchmarkCaseName& val)
    -> std::ostream& {
    return stream << val.str();
}

}  // namespace stat_bench
