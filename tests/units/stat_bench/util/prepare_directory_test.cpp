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

#include <catch2/catch_test_macros.hpp>

#ifdef _WIN32
#else
#include <sys/stat.h>  // stat
#include <unistd.h>    // rmdir
#endif

TEST_CASE("stat_bench::util::prepare_directory_for") {
    SECTION("create directory") {
        const std::string dir_path = "./prepare_directory_test/";
        const std::string file_path = dir_path + "test";

#ifdef _WIN32
        // TODO
#else
        ::rmdir(dir_path.c_str());
        struct stat buf {};
        REQUIRE(::stat(dir_path.c_str(), &buf) != 0);
#endif

        stat_bench::util::prepare_directory_for(file_path);

#ifdef _WIN32
        // TODO
#else
        REQUIRE(::stat(dir_path.c_str(), &buf) == 0);
        REQUIRE(::stat(file_path.c_str(), &buf) != 0);
#endif
    }
}
