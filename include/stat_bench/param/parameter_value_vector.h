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
 * \brief Definition of ParameterValueVector class.
 */
#pragma once

// IWYU pragma: no_include  <stddef.h>
#include <cstddef>
#include <utility>  // IWYU pragma: keep
#include <vector>

#include "stat_bench/param/parameter_value.h"

namespace stat_bench {
namespace param {

/*!
 * \brief Interface of vectors of parameter values.
 */
class IParameterValueVector {
public:
    //! Type of iterators.
    using ConstIterator = std::vector<ParameterValue>::const_iterator;

    /*!
     * \brief Get the iterator of the first element.
     *
     * \return Iterator.
     */
    [[nodiscard]] virtual auto begin() const -> ConstIterator = 0;

    /*!
     * \brief Get the iterator of the past-the-end element.
     *
     * \return Iterator.
     */
    [[nodiscard]] virtual auto end() const -> ConstIterator = 0;

    /*!
     * \brief Get the number of values.
     *
     * \return Number of values.
     */
    [[nodiscard]] virtual auto size() const -> std::size_t = 0;

    IParameterValueVector(const IParameterValueVector&) = delete;
    IParameterValueVector(IParameterValueVector&&) = delete;
    auto operator=(const IParameterValueVector&)
        -> IParameterValueVector& = delete;
    auto operator=(IParameterValueVector&&) -> IParameterValueVector& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~IParameterValueVector() = default;

protected:
    /*!
     * \brief Constructor.
     */
    IParameterValueVector() = default;
};

/*!
 * \brief Class of vectors of parameter values.
 *
 * \tparam T Type of values.
 */
template <typename T>
class ParameterValueVector final : public IParameterValueVector {
public:
    /*!
     * \brief Constructor.
     */
    ParameterValueVector() = default;

    /*!
     * \brief Add a value.
     *
     * \param[in] value Value.
     * \return This.
     */
    auto add(const T& value) -> ParameterValueVector* {
        values_.push_back(std::move(ParameterValue().emplace<T>(value)));
        return this;
    }

    //! \copydoc stat_bench::param::IParameterValueVector::begin
    [[nodiscard]] auto begin() const -> ConstIterator override {
        return values_.begin();
    }

    //! \copydoc stat_bench::param::IParameterValueVector::end
    [[nodiscard]] auto end() const -> ConstIterator override {
        return values_.end();
    }

    //! \copydoc stat_bench::param::IParameterValueVector::size
    [[nodiscard]] auto size() const -> std::size_t override {
        return values_.size();
    }

    ParameterValueVector(const ParameterValueVector&) = delete;
    ParameterValueVector(ParameterValueVector&&) = delete;
    auto operator=(const ParameterValueVector&)
        -> ParameterValueVector& = delete;
    auto operator=(ParameterValueVector&&) -> ParameterValueVector& = delete;

    /*!
     * \brief Destructor.
     */
    ~ParameterValueVector() override = default;

private:
    //! Values.
    std::vector<ParameterValue> values_{};
};

}  // namespace param
}  // namespace stat_bench
