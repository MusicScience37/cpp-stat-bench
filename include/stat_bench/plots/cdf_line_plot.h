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
 * \brief Definition of CdfLinePlot class.
 */
#pragma once

#include <string>

#include "stat_bench/plots/i_plot.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of line plots of cumulative distribution functions.
 */
class CdfLinePlot final : public IPlot {
public:
    /*!
     * \brief Constructor.
     */
    CdfLinePlot() = default;

    CdfLinePlot(const CdfLinePlot&) = delete;
    CdfLinePlot(CdfLinePlot&&) = delete;
    auto operator=(const CdfLinePlot&) -> CdfLinePlot& = delete;
    auto operator=(CdfLinePlot&&) -> CdfLinePlot& = delete;

    /*!
     * \brief Destructor.
     */
    ~CdfLinePlot() override = default;

    //! \copydoc stat_bench::plots::IPlot::name_for_file
    [[nodiscard]] auto name_for_file() const
        -> const util::Utf8String& override;

    //! \copydoc stat_bench::plots::IPlot::write
    void write(const measurer::MeasurementType& measurement_type,
        const BenchmarkGroupName& group_name,
        const std::vector<measurer::Measurement>& measurements,
        const std::string& file_path) override;

private:
    //! Name for output files.
    util::Utf8String name_for_file_{"cdf"};
};

}  // namespace plots
}  // namespace stat_bench
