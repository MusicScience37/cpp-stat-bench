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
 * \brief Implementation of MeasurementConfig class.
 */
#include "stat_bench/measurement_config.h"

#include <utility>

#include "stat_bench/measurer/measurement_type.h"

namespace stat_bench {

MeasurementConfig::MeasurementConfig() : type_("Unnamed Measurement") {}

auto MeasurementConfig::type(std::string value) -> MeasurementConfig& {
    type_ = measurer::MeasurementType(std::move(value));
    return *this;
}

auto MeasurementConfig::samples(std::size_t value) -> MeasurementConfig& {
    samples_ = value;
    return *this;
}

auto MeasurementConfig::warming_up_samples(std::size_t value)
    -> MeasurementConfig& {
    warming_up_samples_ = value;
    return *this;
}

auto MeasurementConfig::iterations(std::size_t value) -> MeasurementConfig& {
    iterations_ = value;
    return *this;
}

auto MeasurementConfig::type() const noexcept
    -> const measurer::MeasurementType& {
    return type_;
}

auto MeasurementConfig::samples() const noexcept -> std::optional<std::size_t> {
    return samples_;
}

auto MeasurementConfig::warming_up_samples() const noexcept
    -> std::optional<std::size_t> {
    return warming_up_samples_;
}

auto MeasurementConfig::iterations() const noexcept
    -> std::optional<std::size_t> {
    return iterations_;
}

}  // namespace stat_bench
