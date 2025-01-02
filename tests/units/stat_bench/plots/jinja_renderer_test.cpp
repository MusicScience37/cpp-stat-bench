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
 * \brief Test of JinjaRenderer class.
 */
#include "stat_bench/plots/jinja_renderer.h"

#include <sstream>
#include <string>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::plots::JinjaRenderer") {
    using stat_bench::plots::JinjaRenderer;

    SECTION("render") {
        JinjaRenderer renderer{};
        const auto name = std::string("test1");
        renderer.load_from_text(name, "{{ var1 }}");
        std::ostringstream out;

        renderer.render_to(out, name, {{"var1", "test text"}});

        CHECK(out.str() == "test text");
    }
}
