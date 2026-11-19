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
#include "core/types/Mesh.h"
#include "core/types/Vec3.h"

namespace us {

class RayMeshIntersection
{
public:
    RayMeshIntersection(MeshPtr aMesh, bool aAccelerate);

    std::tuple<double, Mesh::FaceHandle> intersects(const Vec3 &aOrigin,
                                                    const Vec3 &aDirection) const;

private:
    struct Triangle
    {
        std::array<Vec3, 3> _p;
        Mesh::FaceHandle _f;
        Bounds bounds() const;
    };

    Triangle toTriangle(Mesh &aMesh, Mesh::FaceHandle aFh) const;

    double rayTriangleIntersection(const Vec3 &aOrigin,
                                   const Vec3 &aDirection,
                                   const Triangle &aTriangle) const;

    MeshPtr _mesh;

    using TrianglePtr = std::shared_ptr<Triangle>;
    using TriangleTree = BSPTree<TrianglePtr>;

    class Intersector : public TriangleTree::IBSPVisitor
    {
    public:
        Intersector(const RayMeshIntersection *aParent, const Vec3 &aOrigin, const Vec3 &aDirection);
        void visit(TriangleTree::BSPNode *aNode) override;
        void visit(TriangleTree *aTree) override;

        double _tMin;
        double _tMax;
        double _t;
        Mesh::FaceHandle _fh;
        const Vec3 _origin;
        const Vec3 _direction;
        const RayMeshIntersection *_parent;
    };

    std::unique_ptr<TriangleTree> _tree;
};

} // namespace us
