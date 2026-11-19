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

#include "core/types/Vec3.h"
#include "util/OrderedMap.h"
#include <memory>

namespace us {

/**
 * This class represents a list of 3D points connected by oriented edges.
 * Each point and edge in the data structure is represented by resp.
 * a VertexHandle and an EdgeHandle. These handles remain valid even if
 * points or edges are removed from the Polyline.
 */
class Polyline
{
public:

    ///Base class for a handle.
    class BaseHandle
    {
    public:
        ///Constructs a new handle with given index.
        /// By default it is invalid, meaning its index equals -1
        BaseHandle(int aIdx = -1);
        ///index of the handle
        int idx() const;
        ///returns false when the handle is invalid
        operator bool() const;
        ///returns the handle's index
        operator int() const;
    private:
        int _idx;
    };

    ///Vertex handle
    class VertexHandle : public BaseHandle
    {
    public:
        VertexHandle(int aIdx = -1);
        bool operator==(const VertexHandle &aOther) const;
        bool operator!=(const VertexHandle &aOther) const;
        bool operator<(const VertexHandle &aOther) const;
    };
    ///Edge handle
    class EdgeHandle : public BaseHandle
    {
    public:
        EdgeHandle(int aIdx = -1);
        bool operator==(const EdgeHandle &aOther) const;
        bool operator!=(const EdgeHandle &aOther) const;
        bool operator<(const EdgeHandle &aOther) const;
    };

    /**
     * Constructs a new empty Polyline
     */
    Polyline();
    /**
     * Adds a new point with given coordinates and returns
     * a VertexHandle for this point.
     */
    VertexHandle add(const Vec3 &aPoint);
    /**
     * Removes the point with given handle from this
     * Polyline, if it is still a part of it.
     * As a side-effect all edges connected to
     * the given point are removed as well.
     */
    bool remove(VertexHandle aVertexHandle);
    /**
     * Creates an oriented edge connecting the points
     * with given handles and returns the EdgeHandle
     * of the newly created edge. Or an invalid
     * handle if the edge could not be created.
     * An edge cannot be created when:
     * - it is already defined
     * - its opposite edge is already there
     * - it would cause a point to share more than 2 edges
     * - it would cause a point to be target or source of multiple
     *   edges, messing up the orientation of the Polyline
     */
    EdgeHandle connect(VertexHandle aFrom, VertexHandle aTo);

    /**
     * Removes the edge with given handle from
     * the Polyline, if it was part of it. Returns
     * true on success.
     * No points are removed as a result.
     */
    bool disconnect(EdgeHandle aEdge);

    /**
     * Returns a vertex handle to the start
     * of the edge with given handle
     */
    VertexHandle from(EdgeHandle aEdge) const;
    /**
     * Returns a vertex handle to the end
     * of the edge with given handle
     */
    VertexHandle to(EdgeHandle aEdge) const;

    /**
     * Returns the handle of the edge having
     * the vertex with given handle as the start
     */
    EdgeHandle next(VertexHandle aVertex) const;
    /**
     * Returns the handle of the edge having
     * the vertex with given handle as the end
     */
    EdgeHandle prev(VertexHandle aVertex) const;
    /**
     * Returns the handle of the edge
     * following the edge with given handle
     */
    EdgeHandle next(EdgeHandle aEdge) const;
    /**
     * Returns the handle of the edge
     * preceding the edge with given handle
     */
    EdgeHandle prev(EdgeHandle aEdge) const;
    /**
     * Returns a collection of handles of all
     * points in this Polyline
     */
    std::vector<VertexHandle> vertices() const;
    /**
     * Returns a collection of handles of all
     * edges in this Polyline
     */
    std::vector<EdgeHandle> edges() const;
    /**
     * Returns the coordinates of point with given handle
     */
    Vec3 point(VertexHandle aVh) const;
    /**
     * Returns whether this Polyline has a point with given handle
     */
    bool has(VertexHandle aVh) const;
    /**
     * Returns whether this Polyline has an edge with given handle
     */
    bool has(EdgeHandle aEh) const;
    /**
     * Updates the point with given handle
     */
    void setPoint(VertexHandle aVh, const Vec3 &aCoord);

private:
    OrderedMap<int, Vec3> _points;
    OrderedMap<int, int> _next;
    OrderedMap<int, int> _prev;
    int _nextIndex;
};

using PolylinePtr = std::shared_ptr<Polyline>;

} // namespace us

namespace std {
template<>
struct hash<us::Polyline::VertexHandle>
{
    size_t operator()(const us::Polyline::VertexHandle &aHandle) const;
};

template<>
struct hash<us::Polyline::EdgeHandle>
{
    size_t operator()(const us::Polyline::EdgeHandle &aHandle) const;
};
} // namespace std
