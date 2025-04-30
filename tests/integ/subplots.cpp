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
 * \brief Benchmark with subplots.
 */
#include <cmath>
#include <cstdlib>
#include <memory>
#include <string>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/fixture_base.h"
#include "stat_bench/invocation_context.h"
#include "stat_bench/param/parameter_value_vector.h"
#include "stat_bench/plot_options.h"

/*!
 * \brief Calculate a true value of binomial series for negative exponent.
 *
 * \param[in] x Variable `x`.
 * \param[in] n Variable `n`.
 * \return `(1 + x)^{-n}`.
 */
[[nodiscard]] auto true_binomial_series_for_negative_exponent(
    double x, unsigned int n) -> double {
    return std::pow(1 + x, -static_cast<int>(n));
}

/*!
 * \brief Calculate an approximate value of binomial series for negative
 * exponent using Maclaurin series.
 *
 * \param[in] x Variable `x`.
 * \param[in] n Variable `n`.
 * \return Approximate value of `(1 + x)^{-n}`.
 */
[[nodiscard]] auto approx_binomial_series_for_negative_exponent(
    double x, int n, int num_terms) -> double {
    double result = 1.0;
    double term = 1.0;
    for (int k = 1; k <= num_terms; ++k) {
        term *= static_cast<double>(-n - k + 1) * x / static_cast<double>(k);
        result += term;
    }
    return result;
}

class BinomialSeriesFixture : public stat_bench::FixtureBase {
public:
    BinomialSeriesFixture() {
        add_param<std::string>("Sign")->add("positive")->add("negative");
        add_param<double>("Absolute Value of x")
            ->add(0.1)   // NOLINT
            ->add(0.2)   // NOLINT
            ->add(0.5);  // NOLINT
        add_param<int>("Exponent")
            ->add(1)   // NOLINT
            ->add(2)   // NOLINT
            ->add(3);  // NOLINT
        add_param<int>("Terms")
            ->add(1)    // NOLINT
            ->add(5)    // NOLINT
            ->add(10);  // NOLINT
    }

    void setup(stat_bench::InvocationContext& context) override {
        const auto sign = context.get_param<std::string>("Sign");
        if (sign == "positive") {
            x_ = context.get_param<double>("Absolute Value of x");
        } else {
            x_ = -context.get_param<double>("Absolute Value of x");
        }
        n_ = context.get_param<int>("Exponent");
        num_terms_ = context.get_param<int>("Terms");
        true_value_ = true_binomial_series_for_negative_exponent(x_, n_);
    }

    void tear_down(stat_bench::InvocationContext& context) override {
        context.add_custom_output("Error Rate",
            std::abs((true_value_ - approx_value_) / true_value_));
    }

protected:
    double x_{};
    int n_{};
    int num_terms_{};
    double true_value_{};
    double approx_value_{};
};

STAT_BENCH_CASE_F(BinomialSeriesFixture, "BinomialSeries", "BinomialSeries") {
    STAT_BENCH_MEASURE() {
        approx_value_ =
            approx_binomial_series_for_negative_exponent(x_, n_, num_terms_);
    };
}

STAT_BENCH_GROUP("BinomialSeries")
    .add_parameter_to_output_line_plot("Absolute Value of x", "Error Rate",
        stat_bench::PlotOptions()
            .log_output(true)
            .subplot_column_parameter_name("Exponent")
            .subplot_row_parameter_name("Sign"));

STAT_BENCH_MAIN
