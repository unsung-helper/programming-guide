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

#include <functional>
#include <tuple>

#include "core/types/Bounds.h"

namespace us {

template<class T>
class Grid3D
{
public:
    struct IndexHash;
    typedef T Cell;
    typedef std::tuple<int, int, int> Index;
    typedef typename std::unordered_map<Index, T, IndexHash>::iterator Iterator;
    typedef typename std::unordered_map<Index, T, IndexHash>::const_iterator ConstIterator;

    Grid3D(double aSize)
        : _size(aSize)
    {}

    double size() const { return _size; }

    Cell& operator[](const Index& aIndex)
    {
        if (!has(aIndex)) {
            auto [x, y, z] = aIndex;
            _bounds.add(Vec3(x * _size, y * _size, z * _size));
            _bounds.add(Vec3((x + 1) * _size, (y + 1) * _size, (z + 1) * _size));
            _cells.insert({aIndex, Cell()});
        }
        return _cells[aIndex];
    }

    Cell at(const Index& aIndex) const
    {
        assert(has(aIndex));
        return _cells.at(aIndex);
    }

    bool has(const Index& aIndex) const { return (_cells.find(aIndex) != std::end(_cells)); }

    Index indexOf(const Vec3& aPoint) const
    {
        return Index(int(std::floor(aPoint.x() / _size)),
                     int(std::floor(aPoint.y() / _size)),
                     int(std::floor(aPoint.z() / _size)));
    }

    Index offsetFrom(const Index& aCenter, int aX, int aY, int aZ) const
    {
        return {std::get<0>(aCenter) + aX, std::get<1>(aCenter) + aY, std::get<2>(aCenter) + aZ};
    }

    std::vector<Index> indicesOf(const Bounds& aBounds) const
    {
        Index aMin = indexOf(aBounds.min());
        Index aMax = indexOf(aBounds.max());
        std::vector<Index> result;
        for (int z = std::get<2>(aMin); z <= std::get<2>(aMax); ++z) {
            for (int y = std::get<1>(aMin); y <= std::get<1>(aMax); ++y) {
                for (int x = std::get<0>(aMin); x <= std::get<0>(aMax); ++x) {
                    result.push_back(Index(x, y, z));
                }
            }
        }
        return result;
    }

    const Bounds& bounds() const { return _bounds; }

    struct IndexHash
    {
        std::size_t operator()(const Index& t) const
        {
            const auto& [a, b, c] = t;
            std::size_t seed = 0;
            seed ^= std::hash<int>{}(a) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<int>{}(b) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<int>{}(c) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };

    Iterator begin() { return _cells.begin(); }
    Iterator end() { return _cells.end(); }
    ConstIterator begin() const { return _cells.begin(); }
    ConstIterator end() const { return _cells.end(); }

private:
    std::unordered_map<Index, T, IndexHash> _cells;

    double _size;

    Bounds _bounds;
};

} // namespace us
