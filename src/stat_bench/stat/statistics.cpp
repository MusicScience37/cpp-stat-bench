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
 * \brief Implementation of Statistics class.
 */
#include "stat_bench/stat/statistics.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace stat_bench {
namespace stat {

Statistics::Statistics() = default;

void Statistics::clear() { sorted_samples_.clear(); }

void Statistics::reserve(std::size_t samples) {
    unsorted_samples_.reserve(samples);
    sorted_samples_.reserve(samples);
}

void Statistics::add(double val) {
    unsorted_samples_.push_back(val);
    sorted_samples_.insert(
        std::lower_bound(sorted_samples_.begin(), sorted_samples_.end(), val),
        val);
}

void Statistics::calc() {
    if (sorted_samples_.empty()) {
        throw std::invalid_argument("No sample for statistics.");
    }

    double sum = 0.0;
    max_ = std::numeric_limits<double>::min();
    min_ = std::numeric_limits<double>::max();
    for (double val : sorted_samples_) {
        sum += val;
        if (val > max_) {
            max_ = val;
        }
        if (val < min_) {
            min_ = val;
        }
    }
    mean_ = sum / static_cast<double>(sorted_samples_.size());

    median_ = sorted_samples_.at(sorted_samples_.size() / 2);

    if (sorted_samples_.size() >= 2) {
        double sum_of_squared_deviation = 0.0;
        for (double val : sorted_samples_) {
            double deviation = val - mean_;
            sum_of_squared_deviation += deviation * deviation;
        }
        variance_ = sum_of_squared_deviation /
            static_cast<double>(sorted_samples_.size() - 1);
    } else {
        variance_ = 0.0;
    }

    standard_deviation_ = std::sqrt(variance_);
}

}  // namespace stat
}  // namespace stat_bench
