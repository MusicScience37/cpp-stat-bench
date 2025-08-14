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
 * \brief Implementation of ParameterGenerator class.
 */
#include "stat_bench/param/parameter_generator.h"

#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/util/ordered_map.h"

namespace stat_bench::param {

ParameterGenerator::ParameterGenerator(const std::vector<
    std::pair<ParameterName, std::shared_ptr<IParameterValueVector>>>& params) {
    params_.reserve(params.size());
    for (const auto& param : params) {
        if (param.second->size() == 0) {
            continue;
        }
        params_.push_back(ParamData{param.first, param.second,
            param.second->begin(), param.second->begin(), param.second->end()});
    }
}

auto ParameterGenerator::iterate() -> bool {
    for (auto iter = params_.rbegin(); iter != params_.rend(); ++iter) {
        ++(iter->next);
        if (iter->next != iter->end) {
            return true;
        }
        iter->next = iter->begin;
    }
    return false;
}

auto ParameterGenerator::generate() const -> ParameterDict {
    util::OrderedMap<ParameterName, ParameterValue> data;
    data.reserve(params_.size());
    for (const auto& param : params_) {
        data.try_emplace(param.name, *param.next);
    }
    return ParameterDict(data);
}

}  // namespace stat_bench::param
