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
 * \brief Helper of MsgPack data files.
 */
#pragma once

#include <msgpack_light/serialization_buffer.h>
#include <msgpack_light/type_support/fwd.h>
#include <msgpack_light/type_support/struct.h>
#include <msgpack_light/type_support/unordered_map.h>  // IWYU pragma: keep

#include "stat_bench/reporter/data_file_spec.h"
#include "stat_bench/util/utf8_string.h"

namespace msgpack_light::type_support {

/*!
 * \brief Implementation of msgpack_light::type_support::serialization_traits
 * for stat_bench::util::Utf8String.
 */
template <>
struct serialization_traits<stat_bench::util::Utf8String> {
    /*!
     * \brief Serialize a value.
     *
     * \param[out] buffer Buffer.
     * \param[in] value Value.
     */
    static void serialize(serialization_buffer& buffer,
        const stat_bench::util::Utf8String& value) {
        buffer.serialize(value.str());
    }
};

}  // namespace msgpack_light::type_support

#ifndef STAT_BENCH_DOCUMENTATION

MSGPACK_LIGHT_STRUCT_MAP(stat_bench::reporter::data_file_spec::StatData, mean,
    max, min, median, variance, standard_deviation, standard_error);
MSGPACK_LIGHT_STRUCT_MAP(
    stat_bench::reporter::data_file_spec::DurationData, stat, values);
MSGPACK_LIGHT_STRUCT_MAP(
    stat_bench::reporter::data_file_spec::CustomStatOutputData, name, stat,
    values);
MSGPACK_LIGHT_STRUCT_MAP(
    stat_bench::reporter::data_file_spec::CustomOutputData, name, value);
MSGPACK_LIGHT_STRUCT_MAP(stat_bench::reporter::data_file_spec::MeasurementData,
    group_name, case_name, params, measurer_name, iterations, samples,
    durations, custom_stat_outputs, custom_outputs);
MSGPACK_LIGHT_STRUCT_MAP(stat_bench::reporter::data_file_spec::RootData,
    started_at, finished_at, measurements);

#endif
