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
#include <list>
#include <unordered_set>
#include <vector>

namespace us {

template<typename Key>
class OrderedSet
{
public:
    class const_iterator
    {
    private:
        typename std::list<Key>::const_iterator _it;

    public:
        const_iterator(typename std::list<Key>::const_iterator aIt);

        Key operator*() const;

        const Key* operator->() const;

        const_iterator& operator++();

        const_iterator operator++(int);

        bool operator==(const const_iterator& other) const;

        bool operator!=(const const_iterator& other) const;
    };

    static OrderedSet<Key> fromVector(const std::vector<Key>& aVector);

    bool empty() const;

    void clear();

    const_iterator begin() const;

    const_iterator end() const;

    void insert(Key aKey);

    void insertFront(Key aKey);

    void remove(const Key& aKey);

    bool contains(const Key& aKey) const;

    size_t size() const;

private:
    std::unordered_set<Key> _set;
    std::list<Key> _order;
};

template<typename Key>
OrderedSet<Key>::const_iterator::const_iterator(typename std::list<Key>::const_iterator aIt)
    : _it(aIt)
{}

template<typename Key>
Key OrderedSet<Key>::const_iterator::operator*() const
{
    return *_it;
}

template<typename Key>
const Key* OrderedSet<Key>::const_iterator::operator->() const
{
    return _it; //&(*_it);
}

template<typename Key>
typename OrderedSet<Key>::const_iterator& OrderedSet<Key>::const_iterator::operator++()
{
    ++_it;
    return *this;
}

template<typename Key>
bool OrderedSet<Key>::const_iterator::operator==(
    const typename OrderedSet<Key>::const_iterator& other) const
{
    return _it == other._it;
}

template<typename Key>
bool OrderedSet<Key>::const_iterator::operator!=(const const_iterator& other) const
{
    return _it != other._it;
}

template<typename Key>
typename OrderedSet<Key>::const_iterator OrderedSet<Key>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename Key>
OrderedSet<Key> OrderedSet<Key>::fromVector(const std::vector<Key>& aVector)
{
    OrderedSet<Key> result;
    for (auto& k : aVector) {
        result.insert(k);
    }
    return result;
}

template<typename Key>
bool OrderedSet<Key>::empty() const
{
    return _set.empty();
}

template<typename Key>
void OrderedSet<Key>::clear()
{
    _set.clear();
    _order.clear();
}

template<typename Key>
typename OrderedSet<Key>::const_iterator OrderedSet<Key>::begin() const
{
    return const_iterator(_order.begin());
}

template<typename Key>
typename OrderedSet<Key>::const_iterator OrderedSet<Key>::end() const
{
    return const_iterator(_order.end());
}

template<typename Key>
void OrderedSet<Key>::insert(Key aKey)
{
    if (_set.find(aKey) == _set.end()) {
        _order.push_back(aKey);
    }
    _set.insert(std::move(aKey));
}

template<typename Key>
void OrderedSet<Key>::insertFront(Key aKey)
{
    if (_set.find(aKey) == _set.end()) {
        _order.push_front(aKey);
    }
    _set.insert(std::move(aKey));
}

template<typename Key>
void OrderedSet<Key>::remove(const Key& aKey)
{
    if (_set.erase(aKey)) {
        _order.erase(std::find(_order.begin(), _order.end(), aKey));
    }
}

template<typename Key>
bool OrderedSet<Key>::contains(const Key& aKey) const
{
    return _set.find(aKey) != _set.end();
}

template<typename Key>
size_t OrderedSet<Key>::size() const
{
    return _set.size();
}

} // namespace us
