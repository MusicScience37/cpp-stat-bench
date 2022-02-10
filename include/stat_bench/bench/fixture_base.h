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
 * \brief Definition of FixtureBase class.
 */
#pragma once

#include "stat_bench/bench/benchmark_base.h"
#include "stat_bench/bench/invocation_context.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Base class of fixtures.
 */
class FixtureBase : public BenchmarkBase {
public:
    /*!
     * \brief Setup before running actual process.
     *
     * \note This can be implemented in fixtures to perform common
     * initialization process.
     *
     * \param[in] context Context.
     */
    virtual void setup(InvocationContext& context) {
        // no operation in default implementation
    }

    /*!
     * \brief Tear down after running actual process.
     *
     * \note This can be implemented in fixtures to perform common
     * finalization process.
     * \note This will be called even when errors occurred in run function.
     *
     * \param[in] context Context.
     */
    virtual void tear_down(InvocationContext& context) {
        // no operation in default implementation
    }

    /*!
     * \brief Run actual process in each case.
     *
     * \note This will be implemented in each case, so don't implement in
     * fixtures.
     *
     * \param[in] context Context.
     */
    virtual void run(InvocationContext& context) = 0;

    FixtureBase(const FixtureBase&) = delete;
    FixtureBase(FixtureBase&&) = delete;
    auto operator=(const FixtureBase&) -> FixtureBase& = delete;
    auto operator=(FixtureBase&&) -> FixtureBase& = delete;

    /*!
     * \brief Destructor.
     */
    ~FixtureBase() override = default;

protected:
    /*!
     * \brief Constructor.
     */
    FixtureBase() = default;

private:
    //! \copydoc stat_bench::bench::IBenchmarkCase::execute
    void execute(InvocationContext& context) final {
        setup(context);
        try {
            run(context);
            tear_down(context);
        } catch (...) {
            tear_down(context);
            throw;
        }
    }
};

}  // namespace bench
}  // namespace stat_bench
