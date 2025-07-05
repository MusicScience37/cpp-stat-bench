/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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
 * \brief Definition of MeasurementConfig class.
 */
#pragma once

#include <cstddef>
#include <optional>
#include <string>

#include "stat_bench/measurer/measurement_type.h"

namespace stat_bench {

/*!
 * \brief Class of measurement configurations.
 */
class MeasurementConfig {
public:
    /*!
     * \brief Constructor.
     */
    MeasurementConfig();

    /*!
     * \brief Set the measurement type.
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto type(std::string value) -> MeasurementConfig&;

    /*!
     * \brief Set the number of samples (except for warming up).
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto samples(std::size_t value) -> MeasurementConfig&;

    /*!
     * \brief Set the number of samples for warming up.
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto warming_up_samples(std::size_t value) -> MeasurementConfig&;

    /*!
     * \brief Set the number of iterations.
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto iterations(std::size_t value) -> MeasurementConfig&;

    /*!
     * \brief Apply another configuration for parameters that are not set.
     *
     * \param[in] other Another configuration.
     */
    void apply_if_not_set(const MeasurementConfig& other);

    /*!
     * \brief Get the measurement type.
     *
     * \return Measurement type.
     */
    [[nodiscard]] auto type() const noexcept
        -> const measurer::MeasurementType&;

    /*!
     * \brief Get the number of samples (except for warming up).
     *
     * \return Number of samples.
     */
    [[nodiscard]] auto samples() const noexcept -> std::optional<std::size_t>;

    /*!
     * \brief Get the number of samples for warming up.
     *
     * \return Number of samples for warming up.
     */
    [[nodiscard]] auto warming_up_samples() const noexcept
        -> std::optional<std::size_t>;

    /*!
     * \brief Get the number of iterations.
     *
     * \return Number of iterations.
     */
    [[nodiscard]] auto iterations() const noexcept
        -> std::optional<std::size_t>;

private:
    //! Measurement type.
    measurer::MeasurementType type_;

    //! Number of samples (except for warming up).
    std::optional<std::size_t> samples_;

    //! Number of samples for warming up.
    std::optional<std::size_t> warming_up_samples_;

    //! Number of iterations.
    std::optional<std::size_t> iterations_;
};

}  // namespace stat_bench
