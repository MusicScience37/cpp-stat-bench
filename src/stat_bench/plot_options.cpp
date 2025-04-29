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

PlotOptions::PlotOptions() : log_parameter_(false), log_output_(false) {}

PlotOptions::PlotOptions(PlotOption::Value option)
    : log_parameter_(
          (option & PlotOption::log_parameter) == PlotOption::log_parameter),
      log_output_((option & PlotOption::log_output) == PlotOption::log_output) {
}

auto PlotOptions::log_parameter(bool value) -> PlotOptions& {
    log_parameter_ = value;
    return *this;
}

auto PlotOptions::log_output(bool value) -> PlotOptions& {
    log_output_ = value;
    return *this;
}

auto PlotOptions::log_parameter() const noexcept -> bool {
    return log_parameter_;
}

auto PlotOptions::log_output() const noexcept -> bool { return log_output_; }

}  // namespace stat_bench
