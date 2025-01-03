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
 * \brief Definition of ParameterValue class.
 */
#pragma once

#include <functional>
#include <memory>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <utility>

#include <fmt/format.h>

#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace param {

/*!
 * \brief Class of traits of parameter values.
 *
 * \tparam T Type of value.
 */
template <typename T>
struct ParameterValueTraits {
    /*!
     * \brief Get the type.
     *
     * \return Type info.
     */
    [[nodiscard]] static auto get_type() -> const std::type_info& {
        return typeid(T);
    }

    /*!
     * \brief Format to string.
     *
     * \param[in] data Data.
     * \return Formatted string.
     */
    [[nodiscard]] static auto to_string(const std::shared_ptr<void>& data)
        -> util::Utf8String {
        return util::Utf8String(
            fmt::format("{}", *static_cast<const T*>(data.get())));
    }

    /*!
     * \brief Convert to double.
     *
     * \param[in] data Data.
     * \return Value as double.
     */
    [[nodiscard]] static auto to_double(const std::shared_ptr<void>& data)
        -> double {
        if constexpr (std::is_convertible_v<T, double>) {
            return static_cast<double>(*static_cast<const T*>(data.get()));
        } else {
            throw StatBenchException(
                fmt::format("Cannot convert {} to double.", typeid(T).name()));
        }
    }

    /*!
     * \brief Calculate hash value.
     *
     * \param[in] data Data.
     * \return Hash value.
     */
    [[nodiscard]] static auto calculate_hash(const std::shared_ptr<void>& data)
        -> std::size_t {
        return std::hash<std::type_index>{}(std::type_index(typeid(T))) ^
            std::hash<T>{}(*static_cast<const T*>(data.get()));
    }

    /*!
     * \brief Check whether two values are equal.
     *
     * \param[in] data1 Data.
     * \param[in] data2 Data.
     * \retval true Two values are equal.
     * \retval false Two values are not equal.
     */
    [[nodiscard]] static auto equal(const std::shared_ptr<void>& data1,
        const std::shared_ptr<void>& data2) -> bool {
        return *static_cast<const T*>(data1.get()) ==
            *static_cast<const T*>(data2.get());
    }
};

/*!
 * \brief Class of values of parameters.
 */
class ParameterValue {
public:
    /*!
     * \brief Constructor.
     */
    ParameterValue() noexcept = default;

    /*!
     * \brief Initialize data.
     *
     * \tparam T Type of data.
     * \tparam Args Type of constructor arguments.
     * \param[in] args Constructor arguments.
     * \return This.
     */
    template <typename T, typename... Args>
    auto emplace(Args&&... args) -> ParameterValue& {
        data_ = std::make_shared<T>(std::forward<Args>(args)...);
        get_type_ = &ParameterValueTraits<T>::get_type;
        to_string_ = &ParameterValueTraits<T>::to_string;
        to_double_ = &ParameterValueTraits<T>::to_double;
        calculate_hash_ = &ParameterValueTraits<T>::calculate_hash;
        equal_ = &ParameterValueTraits<T>::equal;
        return *this;
    }

    /*!
     * \brief Clear data.
     */
    void clear() noexcept { data_.reset(); }

    /*!
     * \brief Check data type.
     *
     * \tparam T Type.
     * \return Whether data is a object of type T.
     */
    template <typename T>
    [[nodiscard]] auto is_type_of() const -> bool {
        if (!data_) {
            return false;
        }
        return get_type_() == typeid(T);
    }

    /*!
     * \brief Get value.
     *
     * \tparam T Type.
     * \return Data.
     */
    template <typename T>
    [[nodiscard]] auto as() const -> const T& {
        if (!data_) {
            throw StatBenchException(
                "Tried to get value from empty ParameterValue object.");
        }
        if (!is_type_of<T>()) {
            throw StatBenchException(fmt::format(
                "Wrong type of parameter value (expected: {}, actual: {}).",
                typeid(T).name(), get_type_().name()));
        }
        return *static_cast<const T*>(data_.get());
    }

    /*!
     * \brief Format to string.
     *
     * \return Formatted string.
     */
    [[nodiscard]] auto to_string() const -> util::Utf8String {
        if (!data_) {
            return util::Utf8String("null");
        }
        return to_string_(data_);
    }

    /*!
     * \brief Convert to double.
     *
     * \return Value as double.
     */
    [[nodiscard]] auto to_double() const -> double {
        if (!data_) {
            throw StatBenchException(
                "Tried to convert empty ParameterValue object to double.");
        }
        return to_double_(data_);
    }

    /*!
     * \brief Calculate hash value.
     *
     * \return Hash value.
     */
    [[nodiscard]] auto calculate_hash() const -> std::size_t {
        if (!data_) {
            return 0;
        }
        return calculate_hash_(data_);
    }

    /*!
     * \brief Check whether two values are equal.
     *
     * \param[in] rhs Right-hand-side value.
     * \retval true Two values are equal.
     * \retval false Two values are not equal.
     */
    [[nodiscard]] auto operator==(const ParameterValue& rhs) const -> bool {
        if (!data_ && !rhs.data_) {
            return true;
        }
        if (!data_ || !rhs.data_) {
            return false;
        }
        if (get_type_() != rhs.get_type_()) {
            return false;
        }
        return equal_(data_, rhs.data_);
    }

    /*!
     * \brief Check whether two values are not equal.
     *
     * \param[in] rhs Right-hand-side value.
     * \retval true Two values are not equal.
     * \retval false Two values are equal.
     */
    [[nodiscard]] auto operator!=(const ParameterValue& rhs) const -> bool {
        return !(*this == rhs);
    }

private:
    //! Signature of get_type function.
    using GetTypeSignature = const std::type_info&();

    //! Signature of to_string function.
    using ToStringSignature = util::Utf8String(const std::shared_ptr<void>&);

    //! Signature of to_double function.
    using ToDoubleSignature = double(const std::shared_ptr<void>&);

    //! Signature of calculate_hash function.
    using CalculateHashSignature = std::size_t(const std::shared_ptr<void>&);

    //! Signature of equal function.
    using EqualSignature = bool(
        const std::shared_ptr<void>&, const std::shared_ptr<void>&);

    //! Data.
    std::shared_ptr<void> data_{};

    //! Function to get type.
    GetTypeSignature* get_type_{nullptr};

    //! Function to format to string.
    ToStringSignature* to_string_{nullptr};

    //! Function to convert to double.
    ToDoubleSignature* to_double_{nullptr};

    //! Function to calculate hash value.
    CalculateHashSignature* calculate_hash_{nullptr};

    //! Function to check whether two values are equal.
    EqualSignature* equal_{nullptr};
};

}  // namespace param
}  // namespace stat_bench

namespace std {

/*!
 * \brief Implementation of std::hash for stat_bench::param::ParameterValue.
 */
template <>
class hash<stat_bench::param::ParameterValue> {
public:
    /*!
     * \brief Hash function.
     *
     * \param[in] val Value.
     * \return Hash value.
     */
    auto operator()(const stat_bench::param::ParameterValue& val) const
        -> std::size_t {
        return val.calculate_hash();
    }
};

}  // namespace std
