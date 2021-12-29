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
 * \brief Definition of NullFixture class.
 */
#pragma once

#include "stat_bench/bench/fixture_base.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Class of fixtures without set up and tear down operations.
 *
 */
class NullFixture : public FixtureBase {
public:
    NullFixture(const NullFixture&) = delete;
    NullFixture(NullFixture&&) = delete;
    auto operator=(const NullFixture&) -> NullFixture& = delete;
    auto operator=(NullFixture&&) -> NullFixture& = delete;

    /*!
     * \brief Destructor.
     */
    ~NullFixture() override = default;

protected:
    /*!
     * \brief Constructor.
     */
    NullFixture() = default;

private:
    //! \copydoc stat_bench::bench::FixtureBase::setup
    void setup(InvocationContext& context) final {
        (void)context;
        // no operation
    }

    //! \copydoc stat_bench::bench::FixtureBase::tear_down
    void tear_down(InvocationContext& context) final {
        (void)context;
        // no operation
    }
};

}  // namespace bench
}  // namespace stat_bench
