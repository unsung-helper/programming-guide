/*
 * Copyright (c) 2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */
#pragma once

#include "core/types/Drawing.h"
#include "core/types/Mesh.h"

namespace us {

class DrawingUtil
{
public:
    /**
     * A copy of the given drawing with every curve replaced by line segments.
     *
     * aTolerance is relative, so the result doesn't depend on the drawing's unit or scale:
     * the control points of each piece of curve deviate from its segment at most aTolerance
     * times the length of the piece. For circular arcs this bounds the angle per segment to
     * about 6 * aTolerance radians (curves are halved, so it's often finer): 0.01 turns a
     * circle of any radius into 128 segments.
     */
    static DrawingPtr toLineDrawing(DrawingPtr aDrawing, float aTolerance);

    /**
     * Converts a mesh into a drawing. The boundaries of the mesh are traced and converted
     * into a line drawing. The z coordinate is ignored. By default no fill style is applied,
     * only a black stroke of width 1.
     */
    static DrawingPtr toDrawing(MeshPtr aMesh);

    /**
     * The filled area of the closed subpaths, triangulated in the xy plane; curves are
     * flattened with the relative aTolerance of toLineDrawing
     */
    static MeshPtr toMesh(DrawingPtr aDrawing, float aTolerance);
};

} // namespace us
