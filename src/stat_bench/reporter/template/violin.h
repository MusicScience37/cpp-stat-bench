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
 * @brief Definition of violin variable.
 *
 * This header is automatically generated from
 * src/stat_bench/reporter/template/violin.html.
 * Change this file only via scripts/generate_template_header.py script.
 */
#pragma once

namespace stat_bench {
namespace reporter {

/*!
 * @brief Contents of file
 * src/stat_bench/reporter/template/violin.html.
 */
static constexpr const char* violin = R"(<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <title>{{PLOT_NAME}}</title>
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
    <script src="https://cdn.plot.ly/plotly-2.14.0.min.js"></script>

    <script type="text/javascript">
      var data = "{{DATA}}";
      var layout = {
        title: "{{PLOT_NAME}}",
        yaxis: {
          title: "{{Y_TITLE}}",
          type: "{{Y_TYPE}}",
          constrain: "range",
          range: ["{{Y_MIN}}", "{{Y_MAX}}"],
        },
        showlegend: true,
      };

      Plotly.newPlot("plot", data, layout, {
        scrollZoom: true,
        responsive: true,
      });
    </script>
  </body>
</html>
)";

}  // namespace reporter
}  // namespace stat_bench
