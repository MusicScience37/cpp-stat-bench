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

#include <msgpack.hpp>

#include "stat_bench/reporter/data_file_spec.h"

namespace msgpack {
#ifndef STAT_BENCH_DOCUMENTATION
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
#endif
namespace adaptor {

/*!
 * \brief Specialization of msgpack::adaptor::pack for
 * stat_bench::reporter::data_file_spec::StatData.
 */
template <>
struct pack<stat_bench::reporter::data_file_spec::StatData> {
    /*!
     * \brief Pack a value.
     *
     * \tparam Stream Type of the stream.
     * \param[in] p Packer.
     * \param[in] value Value.
     * \return Stream.
     */
    template <typename Stream>
    auto operator()(packer<Stream>& p,
        const stat_bench::reporter::data_file_spec::StatData& value) const
        -> packer<Stream>& {
        p.pack_map(5);  // NOLINT(readability-magic-numbers)
        p.pack("mean");
        p.pack(value.mean);
        p.pack("max");
        p.pack(value.max);
        p.pack("min");
        p.pack(value.min);
        p.pack("variance");
        p.pack(value.variance);
        p.pack("standard_deviation");
        p.pack(value.standard_deviation);
        return p;
    }
};

/*!
 * \brief Specialization of msgpack::adaptor::pack for
 * stat_bench::reporter::data_file_spec::DurationData.
 */
template <>
struct pack<stat_bench::reporter::data_file_spec::DurationData> {
    /*!
     * \brief Pack a value.
     *
     * \tparam Stream Type of the stream.
     * \param[in] p Packer.
     * \param[in] value Value.
     * \return Stream.
     */
    template <typename Stream>
    auto operator()(packer<Stream>& p,
        const stat_bench::reporter::data_file_spec::DurationData& value) const
        -> packer<Stream>& {
        p.pack_map(2);
        p.pack("stat");
        p.pack(value.stat);
        p.pack("values");
        p.pack(value.values);
        return p;
    }
};

/*!
 * \brief Specialization of msgpack::adaptor::pack for
 * stat_bench::reporter::data_file_spec::CustomStatOutputData.
 */
template <>
struct pack<stat_bench::reporter::data_file_spec::CustomStatOutputData> {
    /*!
     * \brief Pack a value.
     *
     * \tparam Stream Type of the stream.
     * \param[in] p Packer.
     * \param[in] value Value.
     * \return Stream.
     */
    template <typename Stream>
    auto operator()(packer<Stream>& p,
        const stat_bench::reporter::data_file_spec::CustomStatOutputData& value)
        const -> packer<Stream>& {
        p.pack_map(3);
        p.pack("name");
        p.pack(value.name);
        p.pack("stat");
        p.pack(value.stat);
        p.pack("values");
        p.pack(value.values);
        return p;
    }
};

/*!
 * \brief Specialization of msgpack::adaptor::pack for
 * stat_bench::reporter::data_file_spec::CustomOutputData.
 */
template <>
struct pack<stat_bench::reporter::data_file_spec::CustomOutputData> {
    /*!
     * \brief Pack a value.
     *
     * \tparam Stream Type of the stream.
     * \param[in] p Packer.
     * \param[in] value Value.
     * \return Stream.
     */
    template <typename Stream>
    auto operator()(packer<Stream>& p,
        const stat_bench::reporter::data_file_spec::CustomOutputData& value)
        const -> packer<Stream>& {
        p.pack_map(2);
        p.pack("name");
        p.pack(value.name);
        p.pack("value");
        p.pack(value.value);
        return p;
    }
};

/*!
 * \brief Specialization of msgpack::adaptor::pack for
 * stat_bench::reporter::data_file_spec::MeasurementData.
 */
template <>
struct pack<stat_bench::reporter::data_file_spec::MeasurementData> {
    /*!
     * \brief Pack a value.
     *
     * \tparam Stream Type of the stream.
     * \param[in] p Packer.
     * \param[in] value Value.
     * \return Stream.
     */
    template <typename Stream>
    auto operator()(packer<Stream>& p,
        const stat_bench::reporter::data_file_spec::MeasurementData& value)
        const -> packer<Stream>& {
        p.pack_map(9);  // NOLINT(readability-magic-numbers)
        p.pack("group_name");
        p.pack(value.group_name);
        p.pack("case_name");
        p.pack(value.case_name);
        p.pack("params");
        p.pack(value.params);
        p.pack("measurer_name");
        p.pack(value.measurer_name);
        p.pack("iterations");
        p.pack(value.iterations);
        p.pack("samples");
        p.pack(value.samples);
        p.pack("durations");
        p.pack(value.durations);
        p.pack("custom_stat_outputs");
        p.pack(value.custom_stat_outputs);
        p.pack("custom_outputs");
        p.pack(value.custom_outputs);
        return p;
    }
};

/*!
 * \brief Specialization of msgpack::adaptor::pack for
 * stat_bench::reporter::data_file_spec::RootData.
 */
template <>
struct pack<stat_bench::reporter::data_file_spec::RootData> {
    /*!
     * \brief Pack a value.
     *
     * \tparam Stream Type of the stream.
     * \param[in] p Packer.
     * \param[in] value Value.
     * \return Stream.
     */
    template <typename Stream>
    auto operator()(packer<Stream>& p,
        const stat_bench::reporter::data_file_spec::RootData& value) const
        -> packer<Stream>& {
        p.pack_map(3);
        p.pack("started_at");
        p.pack(value.started_at);
        p.pack("finished_at");
        p.pack(value.finished_at);
        p.pack("measurements");
        p.pack(value.measurements);
        return p;
    }
};

}  // namespace adaptor
#ifndef STAT_BENCH_DOCUMENTATION
}  // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
#endif
}  // namespace msgpack
