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
 * \brief Declaration of check_glob_pattern function.
 */
#pragma once

#include <cstddef>  // IWYU pragma: keep
#include <cstring>
#include <string>

#include "stat_bench/stat_bench_exception.h"

namespace stat_bench::util {

/*!
 * \brief Class of view of strings.
 */
class StringView {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Pointer to the string.
     * \param[in] size Size of the string.
     */
    constexpr StringView(const char* data, std::size_t size) noexcept
        : data_(data), size_(size) {}

    /*!
     * \brief Constructor of an empty string.
     */
    constexpr StringView() noexcept : StringView("", 0) {}

    /*!
     * \brief Constructor of implicit conversion from std::string objects.
     *
     * \param[in] str String.
     */
    StringView(  // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
        const std::string& str) noexcept
        : StringView(str.data(), str.size()) {}

    /*!
     * \brief Constructor of implicit conversion from raw string literals.
     *
     * \param[in] str String.
     */
    StringView(  // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
        const char* str) noexcept
        : StringView(str, std::strlen(str)) {}

    /*!
     * \brief Get the pointer to the string.
     *
     * \return Pointer to the string.
     */
    [[nodiscard]] constexpr auto data() const noexcept -> const char* {
        return data_;
    }

    /*!
     * \brief Get the size of the string.
     *
     * \return Size of the string.
     */
    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t {
        return size_;
    }

    /*!
     * \brief Check whether this string is empty.
     *
     * \retval true This string is empty.
     * \retval false This string is not empty.
     */
    [[nodiscard]] constexpr auto empty() const noexcept -> bool {
        return size_ == 0;
    }

    /*!
     * \brief Get a character in the string.
     *
     * \param[in] index Index of the character to get.
     * \return Character.
     */
    [[nodiscard]] auto at(std::size_t index) const -> char {
        if (index >= size_) {
            throw StatBenchException("Invalid index in StringView::at.");
        }
        return data_[index];
    }

    /*!
     * \brief Get a part of the string.
     *
     * \param[in] pos Index of the starting position.
     * \return Created part of the string.
     */
    [[nodiscard]] auto substr(std::size_t pos) const -> StringView {
        if (pos > size_) {
            throw StatBenchException(
                "Invalid arguments in StringView::substr.");
        }
        return StringView(data_ + pos, size_ - pos);
    }

private:
    //! Pointer to the string.
    const char* data_;

    //! Size of the string.
    std::size_t size_;
};

}  // namespace stat_bench::util
