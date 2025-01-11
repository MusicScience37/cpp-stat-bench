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
 * \brief Definition of PlotOption enumeration.
 */
#pragma once

namespace stat_bench {

/*!
 * \brief Enumeration of options for plots.
 */
class PlotOption {
public:
    //! Type of values.
    using Value = unsigned;

    //! No options.
    static constexpr Value none = 0U;

    //! Plot parameters in the log scale.
    static constexpr Value log_parameter = 0x1U;

    //! Plot custom outputs in the log scale.
    static constexpr Value log_output = 0x2U;
};

}  // namespace stat_bench
