/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
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
 * @file
 * @brief Definition of plotly_plot variable.
 *
 * This header is automatically generated from
 * src/stat_bench/reporter/template/plotly_plot.jinja.
 * Change this file only via scripts/generate_template_header.py script.
 */
#pragma once

namespace stat_bench {
namespace reporter {

/*!
 * @brief Contents of file
 * src/stat_bench/reporter/template/plotly_plot.jinja.
 */
static constexpr const char* plotly_plot = R"(<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <title>{{ escape_for_html(title) }}</title>
    <style>
        html,
        body,
        .container {
            height: 100%;
            width: 100%;
            margin: 0px;
        }
    </style>
</head>

<body>
    <div id="plot" class="container"></div>

    <!-- Import Plotly -->
    <script src="https://cdn.plot.ly/plotly-2.26.1.min.js"></script>

    <div id="dataset" style="display:none">
        {{ escape_for_html(dataset) }}
    </div>

    <script type="text/javascript">
        var dataset_str = document.querySelector('#dataset').textContent
        var dataset = JSON.parse(dataset_str);

        Plotly.newPlot("plot", dataset.data, dataset.layout, dataset.config);
    </script>
</body>

</html>
)";

}  // namespace reporter
}  // namespace stat_bench
