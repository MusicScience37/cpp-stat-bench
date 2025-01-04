/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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
 * \brief Definition of OrderedMap class.
 */
#pragma once

#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

namespace stat_bench {
namespace util {

/*!
 * \brief Class of mapping which preserves order of insertion.
 *
 * \tparam Key Type of keys.
 * \tparam MappedValue Type of mapped values.
 */
template <typename Key, typename MappedValue>
class OrderedMap {
public:
    /*!
     * \brief Constructor.
     */
    OrderedMap() = default;

    /*!
     * \brief Access a mapped value.
     *
     * \param[in] key Key.
     * \return Mapped value.
     *
     * \note If the key does not exist, a new pair is inserted.
     */
    [[nodiscard]] auto operator[](const Key& key) -> MappedValue& {
        const auto iter = key_to_index_.find(key);
        if (iter == key_to_index_.end()) {
            pairs_.emplace_back(key, MappedValue{});
            key_to_index_[key] = pairs_.size() - 1;
            return pairs_.back().second;
        }
        return pairs_[iter->second].second;
    }

    /*!
     * \brief Access a mapped value.
     *
     * \param[in] key Key.
     * \return Mapped value.
     *
     * \note If the key does not exist, an exception is thrown.
     */
    [[nodiscard]] auto at(const Key& key) const -> const MappedValue& {
        return pairs_[key_to_index_.at(key)].second;
    }

    /*!
     * \brief Get an iterator pointing to the beginning of pairs.
     *
     * \return Iterator.
     */
    [[nodiscard]] auto begin() const ->
        typename std::vector<std::pair<Key, MappedValue>>::const_iterator {
        return pairs_.begin();
    }

    /*!
     * \brief Get an iterator pointing to the end of pairs.
     *
     * \return Iterator.
     */
    [[nodiscard]] auto end() const ->
        typename std::vector<std::pair<Key, MappedValue>>::const_iterator {
        return pairs_.end();
    }

private:
    //! Pairs.
    std::vector<std::pair<Key, MappedValue>> pairs_;

    //! Mapping from keys to indices.
    std::unordered_map<Key, std::size_t> key_to_index_;
};

}  // namespace util
}  // namespace stat_bench
