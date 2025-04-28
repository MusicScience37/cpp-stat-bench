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
 * \brief Definition of BoxPlot class.
 */
#pragma once

#include <string>

#include "stat_bench/plots/i_plot.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of box plots.
 */
class BoxPlot final : public IPlot {
public:
    /*!
     * \brief Constructor.
     */
    BoxPlot() = default;

    BoxPlot(const BoxPlot&) = delete;
    BoxPlot(BoxPlot&&) = delete;
    auto operator=(const BoxPlot&) -> BoxPlot& = delete;
    auto operator=(BoxPlot&&) -> BoxPlot& = delete;

    /*!
     * \brief Destructor.
     */
    ~BoxPlot() override = default;

    //! \copydoc stat_bench::plots::IPlot::name_for_file
    [[nodiscard]] auto name_for_file() const
        -> const util::Utf8String& override;

    //! \copydoc stat_bench::plots::IPlot::write
    void write(const measurer::MeasurerName& measurer_name,
        const BenchmarkGroupName& group_name,
        const std::vector<measurer::Measurement>& measurements,
        const std::string& file_path) override;

private:
    //! Name for output files.
    util::Utf8String name_for_file_{"box"};
};

}  // namespace plots
}  // namespace stat_bench
