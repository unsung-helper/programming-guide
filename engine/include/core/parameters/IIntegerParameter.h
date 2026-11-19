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

#include "IProductParameter.h"

namespace us {

class IIntegerParameter : public IProductParameter
{
public:

    class Listener {
    public:
        virtual void onValueChanged(IIntegerParameter * aParameter, int aValue) = 0;
        virtual void onMinimumValueChanged(IIntegerParameter * aParameter, int aValue) = 0;
        virtual void onDefaultValueChanged(IIntegerParameter *aParameter, int aValue) = 0;
        virtual void onMaximumValueChanged(IIntegerParameter * aParameter, int aValue) = 0;
        virtual void onDisplayNameChanged(IIntegerParameter *aParameter, const std::string &aName)
            = 0;
        virtual void onUnitChanged(IIntegerParameter *aParameter, std::string aUnit) = 0;
    };

    virtual ~IIntegerParameter();

    virtual int value() const = 0;

    virtual int defaultValue() const = 0;

    virtual bool setValue(int aValue) = 0;

    virtual int minimumValue() const = 0;

    virtual int maximumValue() const = 0;

    virtual std::string unit() const = 0;

    virtual void addListener(Listener * aListener) = 0;

    virtual void removeListener(Listener * aListener) = 0;
};

} // namespace us
