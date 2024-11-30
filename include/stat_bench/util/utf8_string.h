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
 * \brief Definition of Utf8String class.
 */
#pragma once

#include <cstddef>
#include <functional>
#include <ostream>
#include <string>

#include <fmt/base.h>

namespace stat_bench {
namespace util {

/*!
 * \brief Class of UTF-8 encoded string.
 */
class Utf8String {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] str String.
     */
    explicit Utf8String(std::string str);

    /*!
     * \brief Constructor. (Empty string.)
     */
    Utf8String() = default;

    /*!
     * \brief Get the string.
     *
     * \return String.
     */
    [[nodiscard]] auto str() const noexcept -> const std::string&;

private:
    //! String.
    std::string str_;
};

/*!
 * \brief Compare two Utf8String objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The two objects are equal.
 * \retval false The two objects are not equal.
 */
[[nodiscard]] auto operator==(
    const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool;

/*!
 * \brief Compare two Utf8String objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The two objects are not equal.
 * \retval false The two objects are equal.
 */
[[nodiscard]] auto operator!=(
    const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool;

/*!
 * \brief Compare two Utf8String objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The left-hand side object is less than the right-hand side
 * object.
 * \retval false The left-hand side object is not less than the right-hand side
 * object.
 */
[[nodiscard]] auto operator<(
    const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool;

/*!
 * \brief Compare two Utf8String objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The left-hand side object is less than or equal to the
 * right-hand side object.
 * \retval false The left-hand side object is greater than the right-hand side
 * object.
 */
[[nodiscard]] auto operator>(
    const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool;

/*!
 * \brief Compare two Utf8String objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The left-hand side object is less than or equal to the
 * right-hand side object.
 * \retval false The left-hand side object is greater than the right-hand side
 * object.
 */
[[nodiscard]] auto operator<=(
    const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool;

/*!
 * \brief Compare two Utf8String objects.
 *
 * \param[in] lhs Left-hand side object.
 * \param[in] rhs Right-hand side object.
 * \retval true The left-hand side object is greater than or equal to the
 * right-hand side object.
 * \retval false The left-hand side object is less than the right-hand side
 * object.
 */
[[nodiscard]] auto operator>=(
    const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool;

}  // namespace util
}  // namespace stat_bench

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for
 * stat_bench::util::Utf8String.
 */
template <>
struct formatter<stat_bench::util::Utf8String> : public formatter<string_view> {
    /*!
     * \brief Format.
     *
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    auto format(const stat_bench::util::Utf8String& val,
        format_context& context) const -> format_context::iterator;
};

}  // namespace fmt

namespace stat_bench {
namespace util {

/*!
 * \brief Format to a stream.
 *
 * \param[in,out] stream Stream.
 * \param[in] val Value.
 * \return Stream.
 */
auto operator<<(std::ostream& stream, const Utf8String& val) -> std::ostream&;

}  // namespace util
}  // namespace stat_bench

namespace std {

/*!
 * \brief Implementation of std::hash for stat_bench::util::Utf8String.
 */
template <>
class hash<stat_bench::util::Utf8String> {
public:
    /*!
     * \brief Hash function.
     *
     * \param[in] val Value.
     * \return Hash value.
     */
    auto operator()(const stat_bench::util::Utf8String& val) const
        -> std::size_t {
        return hash_(val.str());
    }

private:
    //! Hash function for std::string.
    std::hash<std::string> hash_;
};

}  // namespace std
