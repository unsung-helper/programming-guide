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

class IStringProductOutput : public us::IProductOutput
{
public:
    class Update
    {
    public:
        std::string _value;
        bool _visible;
        std::string _displayName;
        std::string _description;
        std::string _externalID;
    };

    /**
     * Base class for an IStringProductOutput Listener
     */
    class Listener
    {
    public:
        virtual void onUpdate(IStringProductOutput *aOutput, const Update &aUpdate);
    };

    virtual ~IStringProductOutput();

    /**
     * Adds a Listener
     * @note This IStringProductOutput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this IStringProductOutput's lifetime.
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the given Listener
     */
    virtual void removeListener(Listener *aListener) = 0;

    virtual std::string value() const = 0;
};

} // namespace us
