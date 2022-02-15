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
 * \brief Definition of remove_directory function.
 */
#pragma once

#include <string>

#ifdef _WIN32
#include <Windows.h>  // GetFileAttributesA
#include <direct.h>   // _rmdir
#include <fileapi.h>  // GetFileAttributesA
#else
#include <sys/stat.h>  // stat
#include <unistd.h>    // rmdir
#endif

inline void remove_directory(const std::string& dir_path) {
#ifdef _WIN32
    ::_rmdir(dir_path.c_str());
#else
    ::rmdir(dir_path.c_str());
#endif
}
