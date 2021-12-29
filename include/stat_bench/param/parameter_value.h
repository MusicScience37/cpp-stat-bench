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

#include <memory>
#include <typeinfo>
#include <utility>

#include <fmt/format.h>

#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace param {

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
        get_type_ = &ParameterValue::get_type<T>;
        to_string_impl_ = &ParameterValue::to_string_impl<T>;
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
    [[nodiscard]] auto to_string() const -> std::string {
        if (!data_) {
            return "null";
        }
        return to_string_impl_(data_);
    }

private:
    //! Signature of get_type function.
    using GetTypeSignature = const std::type_info&();

    //! Signature of to_string_impl function.
    using ToStringImplSignature = std::string(const std::shared_ptr<void>&);

    /*!
     * \brief Get the type.
     *
     * \tparam T Type.
     * \return Type info.
     */
    template <typename T>
    [[nodiscard]] static auto get_type() -> const std::type_info& {
        return typeid(T);
    }

    /*!
     * \brief Format to string.
     *
     * \tparam T Type of data.
     * \param[in] data Data.
     * \return Formatted string.
     */
    template <typename T>
    [[nodiscard]] static auto to_string_impl(const std::shared_ptr<void>& data)
        -> std::string {
        return fmt::format("{}", *static_cast<const T*>(data.get()));
        ;
    }

    //! Data.
    std::shared_ptr<void> data_{};

    //! Function to get type.
    GetTypeSignature* get_type_{nullptr};

    //! Function to format to string.
    ToStringImplSignature* to_string_impl_{nullptr};
};

}  // namespace param
}  // namespace stat_bench
