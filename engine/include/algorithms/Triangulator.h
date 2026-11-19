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

#include "core/types/Vec2.h"
#include <vector>

namespace us {

class Triangulator
{
public:
    using Vertex = Vec2;
    using Vertices = std::vector<Vertex>;
    using Constraint = std::tuple<int, int>;
    using Constraints = std::vector<Constraint>;
    using Triangle = std::tuple<int, int, int>;
    using Triangles = std::vector<Triangle>;
    using Duplicates = std::unordered_map<int, int>;
    using Triangulation = std::tuple<Vertices, Triangles, Duplicates>;

    Triangulator();

    Triangulator &vertices(const Vertices &aVertices);

    Triangulator &constraints(const Constraints &aConstraints);

    Triangulator &refine(bool aRefine);

    Triangulator &minimumAngle(double aMinAngle);

    Triangulator &removeHoles(bool aRemoveHoles);

    Triangulator &splitBoundary(bool aSplitBoundary);

    Triangulator &splitConstraints(bool aSplitConstraints);

    const Vertices &vertices() const;

    const Constraints &constraints() const;

    bool refine() const;

    double minimumAngle() const;

    bool removeHoles() const;

    bool splitBoundary() const;

    bool splitConstraints() const;

    Triangulation compute() const;

private:
    Vertices _vertices;

    Constraints _constraints;

    bool _refine;

    double _minAngle;

    bool _removeHoles;

    bool _splitBoundary;

    bool _splitConstraints;
};

} // namespace us
