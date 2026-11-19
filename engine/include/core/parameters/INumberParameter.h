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

class INumberParameter : public us::IProductParameter
{
public:
    enum Presentation { Text = 0, Slider = 1, Custom = 2 };

    class Listener {
    public:
        virtual void onValueChanged(INumberParameter * aParameter, float aValue) = 0;
        virtual void onDefaultValueChanged(INumberParameter *aParameter, float aValue) = 0;
        virtual void onMinimumValueChanged(INumberParameter * aParameter, float aValue) = 0;
        virtual void onMaximumValueChanged(INumberParameter * aParameter, float aValue) = 0;
        virtual void onDisplayNameChanged(INumberParameter *aParameter, const std::string &aName) = 0;
        virtual void onVisibleChanged(INumberParameter *aParameter, bool aVisible) = 0;
        virtual void onEditableChanged(INumberParameter *aParameter, bool aEditable) = 0;
        virtual void onExternalIDChanged(INumberParameter *aParameter, std::string aExternalID) = 0;
        virtual void onUnitChanged(INumberParameter *aParameter, std::string aUnit) = 0;
        virtual void onPresentationChanged(INumberParameter *aParameter, Presentation aPresentation)
            = 0;
        virtual void onDescriptionChanged(INumberParameter *aParameter, std::string aDescription) = 0;
    };

    virtual ~INumberParameter();

    virtual float value() const = 0;

    virtual bool setValue(float aValue) = 0;

    virtual float minimumValue() const = 0;

    virtual float maximumValue() const = 0;

    virtual float defaultValue() const = 0;

    virtual std::string unit() const = 0;

    virtual Presentation presentation() const = 0;

    virtual void addListener(Listener * aListener) = 0;

    virtual void removeListener(Listener * aListener) = 0;
};

} // namespace us
