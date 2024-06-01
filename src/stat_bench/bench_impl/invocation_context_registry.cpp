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
 * \brief Implementation of InvocationContextRegistry class.
 */
#include "stat_bench/bench_impl/invocation_context_registry.h"

#include <memory>
#include <utility>

#include "stat_bench/invocation_context.h"
#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace bench_impl {

auto InvocationContextRegistry::instance() -> InvocationContextRegistry& {
    static InvocationContextRegistry registry;
    return registry;
}

auto InvocationContextRegistry::create(BenchmarkCondition cond,
    std::size_t iterations, std::size_t samples,
    std::size_t warming_up_samples) -> InvocationContext& {
    context_ = std::make_unique<InvocationContext>(
        std::move(cond), iterations, samples, warming_up_samples);
    return *context_;
}

void InvocationContextRegistry::clear() noexcept { context_.reset(); }

auto InvocationContextRegistry::get() const -> InvocationContext& {
    if (!context_) {
        throw StatBenchException("No InvocationContext has been created.");
    }
    return *context_;
}

InvocationContextRegistry::InvocationContextRegistry() : context_(nullptr) {}

}  // namespace bench_impl
}  // namespace stat_bench
