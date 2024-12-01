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
 * \brief Implementation of JinjaRenderer class.
 */
#include "stat_bench/reporter/jinja_renderer.h"

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include <fmt/format.h>
#include <inja/inja.hpp>

#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/escape_for_html.h"

namespace stat_bench {
namespace reporter {

//! Internal data.
struct JinjaRenderer::Impl {
public:
    //! Environment.
    inja::Environment env{};

    //! Templates.
    std::unordered_map<std::string, inja::Template> templates{};
};

JinjaRenderer::JinjaRenderer() : impl_(std::make_unique<Impl>()) {
    impl_->env.add_callback(
        "escape_for_html", 1, [](inja::Arguments& args) -> std::string {
            const auto* arg = args.at(0);
            if (arg->is_string()) {
                return util::escape_for_html(arg->get<std::string>());
            }
            return util::escape_for_html(arg->dump());
        });
}

JinjaRenderer::~JinjaRenderer() = default;

void JinjaRenderer::load_from_text(
    util::StringView name, util::StringView text) {
    auto template_obj =
        impl_->env.parse(std::string_view(text.data(), text.size()));
    impl_->env.include_template(
        std::string(name.data(), name.size()), template_obj);
    impl_->templates.try_emplace(
        std::string(name.data(), name.size()), std::move(template_obj));
}

void JinjaRenderer::render_to(
    std::ostream& out, util::StringView name, const nlohmann::json& data) {
    const auto name_str = std::string(name.data(), name.size());
    const auto template_iter = impl_->templates.find(name_str);
    if (template_iter == impl_->templates.end()) {
        throw StatBenchException(
            fmt::format("Invalid name of Jinja template: {}", name_str));
    }

    impl_->env.render_to(out, template_iter->second, data);
}

}  // namespace reporter
}  // namespace stat_bench
