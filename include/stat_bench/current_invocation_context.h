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
 * \brief Definition of current_invocation_context function.
 */
#pragma once

#include "stat_bench/bench_impl/invocation_context_registry.h"
#include "stat_bench/invocation_context.h"

namespace stat_bench {

/*!
 * \brief Get the current invocation context.
 *
 * \return Reference to the current invocation context.
 */
[[nodiscard]] inline auto current_invocation_context() -> InvocationContext& {
    return bench_impl::InvocationContextRegistry::instance().get();
}

}  // namespace stat_bench
