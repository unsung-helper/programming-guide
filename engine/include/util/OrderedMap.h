/*
 * Copyright (c) 2024-2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */
#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace us {

template<typename Key, typename Value>
class OrderedMap
{
public:
    class const_iterator
    {
    private:
        typename std::vector<Key>::const_iterator _it;
        const std::unordered_map<Key, Value>& _map;

    public:
        const_iterator(typename std::vector<Key>::const_iterator aIt,
                       const std::unordered_map<Key, Value>& aMap);

        std::pair<Key, const Value&> operator*() const;

        const_iterator& operator++();

        const_iterator operator++(int);

        bool operator==(const const_iterator& other) const;

        bool operator!=(const const_iterator& other) const;
    };

    class iterator
    {
    public:
        iterator(typename std::vector<Key>::iterator it, std::unordered_map<Key, Value>& map);

        std::pair<const Key&, Value&> operator*();

        iterator& operator++();

        iterator operator++(int);

        bool operator==(const iterator& other) const;

        bool operator!=(const iterator& other) const;

    private:
        typename std::vector<Key>::iterator _it;
        std::unordered_map<Key, Value>& _map;
    };

    bool empty() const;

    void clear();

    const_iterator begin() const;

    const_iterator end() const;

    iterator begin();

    iterator end();

    void insert(const Key& aKey, Value aValue);

    void remove(const Key& aKey);

    Value& at(const Key& aKey);

    const Value& at(const Key& aKey) const;

    const Value& valueAtIndex(int aIdx) const;

    const Key& keyAtIndex(int aIdx) const;

    int indexOf(const Key& aKey) const;

    Value& operator[](const Key& aKey);

    Value value(const Key& aKey, const Value& aDefaultValue) const;

    bool contains(const Key& aKey) const;

    size_t size() const;

private:
    std::unordered_map<Key, Value> _map;
    std::vector<Key> _order;
};

template<typename Key, typename Value>
OrderedMap<Key, Value>::const_iterator::const_iterator(typename std::vector<Key>::const_iterator aIt,
                                                       const std::unordered_map<Key, Value>& aMap)
    : _it(aIt)
    , _map(aMap)
{}

template<typename Key, typename Value>
std::pair<Key, const Value&> OrderedMap<Key, Value>::const_iterator::operator*() const
{
    const Key& key = *_it;
    return {key, _map.at(key)};
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::const_iterator& OrderedMap<Key, Value>::const_iterator::operator++()
{
    ++_it;
    return *this;
}

template<typename Key, typename Value>
bool OrderedMap<Key, Value>::const_iterator::operator==(
    const typename OrderedMap<Key, Value>::const_iterator& other) const
{
    return _it == other._it;
}

template<typename Key, typename Value>
bool OrderedMap<Key, Value>::const_iterator::operator!=(const const_iterator& other) const
{
    return _it != other._it;
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::const_iterator OrderedMap<Key, Value>::const_iterator::operator++(
    int)
{
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename Key, typename Value>
OrderedMap<Key, Value>::iterator::iterator(typename std::vector<Key>::iterator it,
                                           std::unordered_map<Key, Value>& map)
    : _it(it)
    , _map(map)
{}

template<typename Key, typename Value>
std::pair<const Key&, Value&> OrderedMap<Key, Value>::iterator::operator*()
{
    Key& key = *_it;
    return {key, _map.at(key)};
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::iterator& OrderedMap<Key, Value>::iterator::operator++()
{
    ++_it;
    return *this;
}

template<typename Key, typename Value>
bool OrderedMap<Key, Value>::iterator::operator==(const iterator& other) const
{
    return _it == other._it;
}

template<typename Key, typename Value>
bool OrderedMap<Key, Value>::iterator::operator!=(const iterator& other) const
{
    return _it != other._it;
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::iterator OrderedMap<Key, Value>::iterator::operator++(int)
{
    iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename Key, typename Value>
bool OrderedMap<Key, Value>::empty() const
{
    return _map.empty();
}

template<typename Key, typename Value>
void OrderedMap<Key, Value>::clear()
{
    _order.clear();
    _map.clear();
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::const_iterator OrderedMap<Key, Value>::begin() const
{
    return const_iterator(_order.begin(), _map);
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::const_iterator OrderedMap<Key, Value>::end() const
{
    return const_iterator(_order.end(), _map);
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::iterator OrderedMap<Key, Value>::begin()
{
    return iterator(_order.begin(), _map);
}

template<typename Key, typename Value>
typename OrderedMap<Key, Value>::iterator OrderedMap<Key, Value>::end()
{
    return iterator(_order.end(), _map);
}

template<typename Key, typename Value>
void OrderedMap<Key, Value>::insert(const Key& aKey, Value aValue)
{
    if (_map.find(aKey) == _map.end()) {
        _order.push_back(aKey);
    }
    _map[aKey] = std::move(aValue);
}

template<typename Key, typename Value>
void OrderedMap<Key, Value>::remove(const Key& aKey)
{
    if (_map.erase(aKey)) {
        _order.erase(std::find(_order.begin(), _order.end(), aKey));
    }
}

template<typename Key, typename Value>
Value& OrderedMap<Key, Value>::at(const Key& aKey)
{
    return _map.at(aKey);
}

template<typename Key, typename Value>
const Value& OrderedMap<Key, Value>::valueAtIndex(int aIdx) const
{
    return _map.at(_order.at(aIdx));
}

template<typename Key, typename Value>
const Key& OrderedMap<Key, Value>::keyAtIndex(int aIdx) const
{
    return _order.at(aIdx);
}

template<typename Key, typename Value>
int OrderedMap<Key, Value>::indexOf(const Key& aKey) const
{
    for (int i = 0; i < _order.size(); ++i) {
        if (aKey == _order.at(i)) {
            return i;
        }
    }
    return -1;
}

template<typename Key, typename Value>
const Value& OrderedMap<Key, Value>::at(const Key& aKey) const
{
    return _map.at(aKey);
}

template<typename Key, typename Value>
Value& OrderedMap<Key, Value>::operator[](const Key& aKey)
{
    if (_map.find(aKey) == std::end(_map)) {
        insert(aKey, Value());
    }
    return _map[aKey];
}

template<typename Key, typename Value>
Value OrderedMap<Key, Value>::value(const Key& aKey, const Value& aDefaultValue) const
{
    auto it = _map.find(aKey);
    return (it != std::end(_map)) ? it->second : aDefaultValue;
}

template<typename Key, typename Value>
bool OrderedMap<Key, Value>::contains(const Key& aKey) const
{
    return _map.find(aKey) != _map.end();
}

template<typename Key, typename Value>
size_t OrderedMap<Key, Value>::size() const
{
    return _map.size();
}

} // namespace us
