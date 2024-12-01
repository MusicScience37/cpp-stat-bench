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
 * \brief Implementation of MeasurerName class.
 */
#include "stat_bench/measurer/measurer_name.h"

namespace stat_bench {
namespace measurer {

MeasurerName::MeasurerName(util::Utf8String str) noexcept
    : str_(std::move(str)) {}

auto MeasurerName::str() const noexcept -> const util::Utf8String& {
    return str_;
}

}  // namespace measurer
}  // namespace stat_bench