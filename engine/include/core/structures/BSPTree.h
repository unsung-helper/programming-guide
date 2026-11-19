#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "core/types/Bounds.h"

namespace us {

template<typename T>
class BSPTree
{
public:
    using BoundsProvider = std::function<Bounds(const T &)>;

    struct BSPNode;

    class IBSPVisitor
    {
    public:
        virtual void visit(BSPNode *aNode) = 0;
        virtual void visit(BSPTree *aTree) = 0;
    };

    struct BSPNode
    {
        static constexpr int LEAF = -1;
        static constexpr int X = 0;
        static constexpr int Y = 1;
        static constexpr int Z = 2;
        BSPNode()
            : _dim(LEAF)
            , _split(0.0)
        {}
        BSPNode(int aRemainingDepth, const std::vector<T> &aEntries, BoundsProvider aBoundsProvider)
        {
            if (aRemainingDepth == 0 || aEntries.size() < 10) {
                _dim = LEAF;
                _split = 0.0;
                _elements = aEntries;
            } else {
                Bounds bounds;
                for (auto &e : aEntries) {
                    Bounds b = aBoundsProvider(e);
                    bounds.add(b.min());
                    bounds.add(b.max());
                }

                Vec3 m = bounds.min();
                Vec3 M = bounds.max();
                std::vector<T> low, high;

                const Vec3 extent = M - m;
                if (extent.x() > extent.y()) {
                    if (extent.x() > extent.z()) {
                        _dim = X;
                    } else {
                        _dim = Z;
                    }
                } else if (extent.y() > extent.z()) {
                    _dim = Y;
                } else {
                    _dim = Z;
                }

                _split = (M[_dim] + m[_dim]) * 0.5;

                for (auto &e : aEntries) {
                    Bounds b = aBoundsProvider(e);
                    if (b.min()[_dim] <= _split) {
                        low.push_back(e);
                    }
                    if (b.max()[_dim] >= _split) {
                        high.push_back(e);
                    }
                }
                _low = std::make_unique<BSPNode>(aRemainingDepth - 1, low, aBoundsProvider);
                _high = std::make_unique<BSPNode>(aRemainingDepth - 1, high, aBoundsProvider);
            }
        }

        void accept(IBSPVisitor *aVisitor) { aVisitor->visit(this); }

        int _dim;
        double _split;
        std::unique_ptr<BSPNode> _low;
        std::unique_ptr<BSPNode> _high;
        std::vector<T> _elements;
    };

    BSPTree(const std::vector<T> &aElements, BoundsProvider aBounds)
    {
        for (auto &e : aElements) {
            auto bounds = aBounds(e);
            _bounds.add(bounds.min());
            _bounds.add(bounds.max());
        }
        const int maxDepth = std::max(0, int(std::log(aElements.size()) / std::log(2)) - 3);
        _root = std::make_unique<BSPNode>(maxDepth, aElements, aBounds);
    }

    void accept(IBSPVisitor *aVisitor) { aVisitor->visit(this); }

    Bounds _bounds;
    std::unique_ptr<BSPNode> _root;
};

} // namespace us
