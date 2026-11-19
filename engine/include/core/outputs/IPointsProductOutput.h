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

#include "IProductOutput.h"
#include "core/types/PointsMaterial.h"
#include "core/types/Vec3.h"
#include <memory>

namespace us {

class IPointsProductOutput : public us::IProductOutput
{
public:
    class Geometry
    {
    public:
        using Buffer = std::vector<float>;
        Buffer _points;
        Buffer _colors;
        std::vector<std::string> _labels;
    };

    class Update
    {
    public:
        std::shared_ptr<Geometry> _geometry;
        std::shared_ptr<PointsMaterial> _material;
        std::vector<Transformation> _instances;
        bool _visible;
        std::string _displayName;
        std::string _description;
        std::string _externalID;
    };

    /**
     * Base class for an IPointsProductOutput Listener
     */
    class Listener
    {
    public:
        virtual void onUpdate(IPointsProductOutput *aOutput, const Update &aUpdate);
    };

    virtual ~IPointsProductOutput();

    /**
     * Adds a Listener
     * @note This IPointsProductOutput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this IPointsProductOutput's lifetime.
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the given Listener
     */
    virtual void removeListener(Listener *aListener) = 0;
};

} // namespace us
