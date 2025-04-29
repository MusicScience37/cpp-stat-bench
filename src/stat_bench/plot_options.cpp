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
 * \brief Implementation of PlotOptions class.
 */
#include "stat_bench/plot_options.h"

#include "stat_bench/plot_option.h"

namespace stat_bench {

PlotOptions::PlotOptions() noexcept
    : log_parameter_(false), log_output_(false) {}

PlotOptions::PlotOptions(PlotOption::Value option) noexcept
    : log_parameter_(
          (option & PlotOption::log_parameter) == PlotOption::log_parameter),
      log_output_((option & PlotOption::log_output) == PlotOption::log_output) {
}

auto PlotOptions::log_parameter(bool value) noexcept -> PlotOptions& {
    log_parameter_ = value;
    return *this;
}

auto PlotOptions::log_output(bool value) noexcept -> PlotOptions& {
    log_output_ = value;
    return *this;
}

auto PlotOptions::subplot_column_parameter_name(
    const util::StringView& value) noexcept -> PlotOptions& {
    subplot_column_parameter_name_ = value;
    return *this;
}

auto PlotOptions::subplot_row_parameter_name(
    const util::StringView& value) noexcept -> PlotOptions& {
    subplot_row_parameter_name_ = value;
    return *this;
}

auto PlotOptions::log_parameter() const noexcept -> bool {
    return log_parameter_;
}

auto PlotOptions::log_output() const noexcept -> bool { return log_output_; }

auto PlotOptions::subplot_column_parameter_name() const noexcept
    -> util::StringView {
    return subplot_column_parameter_name_;
}

auto PlotOptions::subplot_row_parameter_name() const noexcept
    -> util::StringView {
    return subplot_row_parameter_name_;
}

}  // namespace stat_bench
