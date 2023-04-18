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
 * \brief documentation of namespaces
 */

/*!
 * \dir include/stat_bench
 * \brief Directory of stat_bench source codes.
 */

//! Namespace of stat_bench source codes.
namespace stat_bench {

    /*!
     * \dir include/stat_bench/bench_impl
     * \brief Directory of internal implementation.
     */

    //! Namespace of internal implementation.
    namespace bench_impl {}

    //! Namespace of internal implementation.
    namespace impl {}

    /*!
     * \dir include/stat_bench/clock
     * \brief Directory of clocks for benchmarks.
     */

    //! Namespace of clocks for benchmarks.
    namespace clock {}

    /*!
     * \dir include/stat_bench/filters
     * \brief Directory of filters of benchmarks.
     */

    //! Namespace of filters of benchmarks.
    namespace filters {}

    /*!
     * \dir include/stat_bench/measurer
     * \brief Directory of classes to measure time in benchmarks.
     */

    //! Namespace of classes to measure time in benchmarks.
    namespace measurer {}

    /*!
     * \dir include/stat_bench/param
     * \brief Directory of parameters of benchmarks.
     */

    //! Namespace of parameters of benchmarks.
    namespace param {}

    /*!
     * \dir include/stat_bench/reporter
     * \brief Directory of reporters of results of benchmarks.
     */

    //! Namespace of reporters of results of benchmarks.
    namespace reporter {

        //! Namespace of specification of data files.
        namespace data_file_spec {}

    }  // namespace reporter

    /*!
     * \dir include/stat_bench/runner
     * \brief Directory of classes to run benchmarks.
     */

    //! Namespace of classes to run benchmarks.
    namespace runner {}

    /*!
     * \dir include/stat_bench/stat
     * \brief Directory of statistics.
     */

    //! Namespace of statistics.
    namespace stat {}

    /*!
     * \dir include/stat_bench/util
     * \brief Directory of utility functions and classes.
     */

    //! Namespace of utility functions and classes.
    namespace util {}

}  // namespace stat_bench

//! Namespace of [fmt](https://fmt.dev/) library.
namespace fmt {}
