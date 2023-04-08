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
 * \brief Test of escape_for_html function.
 */
#include "stat_bench/util/escape_for_html.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::util::escape_for_html") {
    using stat_bench::util::escape_for_html;

    SECTION("escape ASCII characters") {
        const std::string input = R"( !"#$%&'()*+,-./0123456789:;<=>?)"
                                  R"(@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_)"
                                  R"(`abcdefghijklmnopqrstuvwxyz{|}~)";

        const std::string output = escape_for_html(input);

        const std::string expected_output =
            R"( !&quot;#$%&amp;&#x27;()*+,-./0123456789:;&lt;=&gt;?)"
            R"(@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_)"
            R"(`abcdefghijklmnopqrstuvwxyz{|}~)";
        CHECK(output == expected_output);
    }
}
