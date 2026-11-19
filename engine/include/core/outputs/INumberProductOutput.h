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

namespace us {

class INumberProductOutput : public us::IProductOutput
{
public:
    class Update
    {
    public:
        float _number = 0.0f;
        std::string _unit;
        bool _visible = true;
        std::string _displayName;
        std::string _description;
        std::string _externalID;
    };

    /**
     * Base class for an INumberProductOutput Listener
     */
    class Listener
    {
    public:
        virtual void onUpdate(INumberProductOutput *aOutput, const Update &aUpdate);
    };

    virtual ~INumberProductOutput();

    /**
     * Adds a Listener
     * @note This INumberProductOutput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this INumberProductOutput's lifetime.
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the given Listener
     */
    virtual void removeListener(Listener *aListener) = 0;

    virtual std::string unit() const = 0;

    virtual float value() const = 0;
};

} // namespace us
