/*
 * Copyright 2021 MusicScience37 (Kenta Kabashima)
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
 * \brief Test of prepare_directory function.
 */
#include "stat_bench/util/prepare_directory.h"

#include <filesystem>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::util::prepare_directory_for") {
    SECTION("create directory") {
        const std::string dir_path = "./prepare_directory_test/";
        const std::string file_path = dir_path + "test";

        std::filesystem::remove_all(dir_path);
        REQUIRE(!std::filesystem::exists(dir_path));

        stat_bench::util::prepare_directory_for(file_path);

        REQUIRE(std::filesystem::exists(dir_path));
        REQUIRE(std::filesystem::is_directory(dir_path));
    }
}
