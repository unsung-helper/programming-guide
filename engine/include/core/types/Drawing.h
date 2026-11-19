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

#include "core/types/Color.h"
#include "core/types/Vec3.h"
#include <memory>
#include <vector>
namespace us {

class Drawing
{
public:
    struct LineComponent;
    struct QuadricComponent;
    struct CubicComponent;

    class IPathComponentVisitor
    {
    public:
        virtual ~IPathComponentVisitor() = default;
        virtual void visit(LineComponent *aComponent);
        virtual void visit(QuadricComponent *aComponent);
        virtual void visit(CubicComponent *aComponent);
    };

    struct PathComponent
    {
        virtual ~PathComponent() = default;
        virtual void accept(IPathComponentVisitor *aVisitor) = 0;
    };

    using PathComponentPtr = std::unique_ptr<PathComponent>;

    struct LineComponent : public PathComponent
    {
        LineComponent(const Vec2 aTarget)
            : _target(aTarget)
        {}
        void accept(IPathComponentVisitor *aVisitor) override;
        Vec2 _target;
    };

    struct QuadricComponent : public PathComponent
    {
        QuadricComponent(const Vec2 aTarget, const Vec2 aControl)
            : _target(aTarget)
            , _control(aControl)
        {}
        void accept(IPathComponentVisitor *aVisitor) override;
        Vec2 _target;
        Vec2 _control;
    };

    struct CubicComponent : public PathComponent
    {
        CubicComponent(const Vec2 aTarget, const Vec2 aControl0, const Vec2 aControl1)
            : _target(aTarget)
            , _control0(aControl0)
            , _control1(aControl1)
        {}
        void accept(IPathComponentVisitor *aVisitor) override;
        Vec2 _target;
        Vec2 _control0;
        Vec2 _control1;
    };

    /**
     * A contour: starts at _position and follows its components, like an svg subpath
     * (a moveto followed by drawing commands)
     */
    struct SubPath
    {
        SubPath() {}

        SubPath(const SubPath &aOther);

        SubPath(SubPath &&aOther) = default;

        SubPath &operator=(const SubPath &aOther);

        SubPath &operator=(SubPath &&aOther) = default;

        Vec2 _position;
        // whether the last point connects back to _position
        bool _closed = false;
        std::vector<PathComponentPtr> _components;

        void accept(IPathComponentVisitor *aVisitor);
    };

    /**
     * Subpaths that are painted together, like an svg path: the fill rule applies to all
     * of them at once, so a subpath can cut a hole in another one.
     */
    struct Path
    {
        enum class FillRule {
            NonZero,
            EvenOdd,
        };

        Color _fillColor;
        // 0 means not filled
        float _fillOpacity = 1.0f;
        Color _strokeColor;
        // 0 means not stroked
        float _strokeOpacity = 1.0f;
        float _strokeWidth = 0.0f;
        FillRule _fillRule = FillRule::NonZero;
        std::vector<SubPath> _subPaths;

        /**
         * Appends an empty subpath; the reference is valid until the next one is added
         */
        SubPath &addSubPath();

        /**
         * Visits the components of all subpaths, in order
         */
        void accept(IPathComponentVisitor *aVisitor);
    };

    struct Bounds
    {
        Vec2 _min;
        Vec2 _max;
        Bounds();
    };

    Drawing() {}

    Drawing(Bounds aBounds);

    virtual ~Drawing();

    Drawing(const Drawing &aOther);

    Drawing(Drawing &&aOther);

    Drawing &operator=(const Drawing &aOther);

    Drawing &operator=(Drawing &&aOther);

    Path *addPath();

    /**
     * The paths, in drawing order
     */
    std::vector<Path *> paths() const;

    void removePath(Path *aPath);

    void accept(IPathComponentVisitor *aVisitor);

    void setBounds(Bounds aBounds);

    void resetBounds();

    Bounds *bounds() const;

private:
    std::vector<std::unique_ptr<Path>> _paths;

    std::unique_ptr<Bounds> _bounds;
};

using DrawingPtr = std::shared_ptr<Drawing>;

} // namespace us
