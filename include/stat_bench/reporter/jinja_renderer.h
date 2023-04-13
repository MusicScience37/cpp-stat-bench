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
 * \file
 * \brief Definition of JinjaRenderer class.
 */
#pragma once

#include <memory>
#include <ostream>

#include <nlohmann/json.hpp>

#include "stat_bench/util/string_view.h"

namespace stat_bench {
namespace reporter {

/*!
 * \brief Class to render Jinja templates.
 */
class JinjaRenderer {
public:
    /*!
     * \brief Constructor.
     */
    JinjaRenderer();

    /*!
     * \brief Destructor.
     */
    ~JinjaRenderer();

    JinjaRenderer(const JinjaRenderer&) = delete;
    JinjaRenderer(JinjaRenderer&&) = delete;
    auto operator=(const JinjaRenderer&) = delete;
    auto operator=(JinjaRenderer&&) = delete;

    /*!
     * \brief Load a template from a text.
     *
     * \param[in] name Name of the template.
     * \param[in] text Text of the template.
     */
    void load_from_text(util::StringView name, util::StringView text);

    /*!
     * \brief Render a template to a stream.
     *
     * \param[out] out Output stream.
     * \param[in] name Name of the template.
     * \param[in] data Data for the template.
     */
    void render_to(
        std::ostream& out, util::StringView name, const nlohmann::json& data);

private:
    //! Internal data.
    struct Impl;

    //! Internal data.
    std::unique_ptr<Impl> impl_;
};

}  // namespace reporter
}  // namespace stat_bench
