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
#include "core/structures/BSPTree.h"
#include "core/types/Bounds.h"
#include "core/types/Polyline.h"
#include "core/types/Vec3.h"

namespace us {

class RayPolylineIntersection
{
public:
    RayPolylineIntersection(PolylinePtr aPolyline, double aPrecision, bool aAccelerate);

    std::tuple<double, bool, Vec3> intersects(const Vec3 &aOrigin, const Vec3 &aDirection) const;

private:
    struct Element
    {
        std::vector<Vec3> _p;
        Bounds bounds() const;        
    };
    using ElementPtr = std::shared_ptr<Element>;
    using ElementTree = BSPTree<ElementPtr>;

    std::pair<double, Vec3> rayElementIntersection(const Vec3 &aOrigin,
                                                   const Vec3 &aDirection,
                                                   const Element &aElement) const;

    class Intersector : public ElementTree::IBSPVisitor
    {
    public:
        Intersector(const RayPolylineIntersection *aParent,
                    const Vec3 &aOrigin,
                    const Vec3 &aDirection);
        void visit(ElementTree::BSPNode *aNode) override;
        void visit(ElementTree *aTree) override;

        double _tMin;
        double _tMax;
        double _t;
        bool _intersects;
        Vec3 _point;
        const Vec3 _origin;
        const Vec3 _direction;
        const RayPolylineIntersection *_parent;
    };

    std::vector<ElementPtr> _elements;

    std::unique_ptr<ElementTree> _tree;

    double _precision;
};

} // namespace us
