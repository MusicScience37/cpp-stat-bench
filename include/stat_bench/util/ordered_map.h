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
#include <initializer_list>
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
    //! Type of iterators.
    using const_iterator =
        typename std::vector<std::pair<Key, MappedValue>>::const_iterator;

    /*!
     * \brief Constructor.
     */
    OrderedMap() = default;

    /*!
     * \brief Constructor.
     *
     * \param[in] initializer_list Initializer list.
     */
    OrderedMap(
        std::initializer_list<std::pair<Key, MappedValue>> initializer_list) {
        for (auto& pair : initializer_list) {
            emplace(std::move(pair.first), std::move(pair.second));
        }
    }

    /*!
     * \brief Check whether this mapping is empty.
     *
     * \retval true This mapping is empty.
     * \retval false This mapping is not empty.
     */
    [[nodiscard]] auto empty() const noexcept -> bool {
        return key_to_index_.empty();
    }

    /*!
     * \brief Get the number of pairs.
     *
     * \return Number of pairs.
     */
    [[nodiscard]] auto size() const noexcept -> std::size_t {
        return key_to_index_.size();
    }

    /*!
     * \brief Count the number of pairs with a key.
     *
     * \param[in] key Key.
     * \return Number of pairs with the key.
     */
    [[nodiscard]] auto count(const Key& key) const -> std::size_t {
        return key_to_index_.count(key);
    }

    /*!
     * \brief Reserve memory space.
     *
     * \param[in] size Number of pairs.
     */
    void reserve(std::size_t size) {
        key_to_index_.reserve(size);
        pairs_.reserve(size);
    }

    /*!
     * \brief Insert a pair.
     *
     * \tparam Args Types of arguments.
     * \param[in] args Arguments.
     * \return A pair of the iterator and whether the insertion is successful.
     */
    template <typename... Args>
    auto emplace(Args&&... args) -> std::pair<const_iterator, bool> {
        pairs_.emplace_back(std::forward<Args>(args)...);
        const auto [iter, success] =
            key_to_index_.emplace(pairs_.back().first, pairs_.size() - 1);
        return {pairs_.begin() + static_cast<std::ptrdiff_t>(iter->second),
            success};
    }

    /*!
     * \brief Erase a pair.
     *
     * \param[in] iter Iterator pointing to the pair.
     * \return Iterator pointing to the next pair.
     */
    auto erase(const_iterator iter) -> const_iterator {
        const auto index = iter - pairs_.begin();
        key_to_index_.erase(pairs_[index].first);
        pairs_.erase(iter);
        for (std::size_t i = index; i < pairs_.size(); ++i) {
            key_to_index_[pairs_[i].first] = i;
        }
        return pairs_.begin() + static_cast<std::ptrdiff_t>(index);
    }

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
     * \brief Find a pair with a key.
     *
     * \param[in] key Key.
     * \return Iterator pointing to the pair. If not found, end() is returned.
     */
    [[nodiscard]] auto find(const Key& key) const -> const_iterator {
        const auto iter = key_to_index_.find(key);
        if (iter == key_to_index_.end()) {
            return pairs_.end();
        }
        return pairs_.begin() + static_cast<std::ptrdiff_t>(iter->second);
    }

    /*!
     * \brief Get an iterator pointing to the beginning of pairs.
     *
     * \return Iterator.
     */
    [[nodiscard]] auto begin() const -> const_iterator {
        return pairs_.begin();
    }

    /*!
     * \brief Get an iterator pointing to the end of pairs.
     *
     * \return Iterator.
     */
    [[nodiscard]] auto end() const -> const_iterator { return pairs_.end(); }

    /*!
     * \brief Check whether this is equal to another mapping.
     *
     * \param[in] rhs Right-hand-side mapping.
     * \retval true This is equal to the right-hand-side mapping.
     * \retval false This is not equal to the right-hand-side mapping.
     */
    [[nodiscard]] auto operator==(const OrderedMap& rhs) const -> bool {
        if (key_to_index_.size() != rhs.key_to_index_.size()) {
            return false;
        }
        return std::all_of(key_to_index_.begin(), key_to_index_.end(),
            [this, &rhs](const auto& pair) {
                const auto rhs_iter = rhs.key_to_index_.find(pair.first);
                return rhs_iter != rhs.key_to_index_.end() &&
                    pairs_[pair.second].second ==
                    rhs.pairs_[rhs_iter->second].second;
            });
    }

    /*!
     * \brief Check whether this is not equal to another mapping.
     *
     * \param[in] rhs Right-hand-side mapping.
     * \retval true This is not equal to the right-hand-side mapping.
     * \retval false This is equal to the right-hand-side mapping.
     */
    [[nodiscard]] auto operator!=(const OrderedMap& rhs) const -> bool {
        return !(*this == rhs);
    }

private:
    //! Pairs.
    std::vector<std::pair<Key, MappedValue>> pairs_;

    //! Mapping from keys to indices.
    std::unordered_map<Key, std::size_t> key_to_index_;
};

}  // namespace util
}  // namespace stat_bench
