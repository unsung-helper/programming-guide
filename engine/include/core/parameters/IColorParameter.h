/*
 * Copyright (c) 2024 Jucon BV
 * All rights reserved.
 *
 * This file is part of dsign. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */

#pragma once

#include "IProductParameter.h"
#include "core/types/Color.h"

namespace us {

class IColorParameter : public us::IProductParameter
{
public:
    class Listener {
    public:
        virtual void onValueChanged(IColorParameter *aParameter, const Color &aValue) = 0;
        virtual void onDefaultValueChanged(IColorParameter *aParameter, const Color &aValue) = 0;
        virtual void onDisplayNameChanged(IColorParameter *aParameter, const std::string &aName) = 0;
        virtual void onVisibleChanged(IColorParameter *aParameter, bool aVisible) = 0;
        virtual void onEditableChanged(IColorParameter *aParameter, bool aEditable) = 0;
        virtual void onExternalIDChanged(IColorParameter *aParameter, std::string aExternalID) = 0;
        virtual void onDescriptionChanged(IColorParameter *aParameter, std::string aDescription) = 0;
    };

    virtual ~IColorParameter();

    virtual Color value() const = 0;

    virtual bool setValue(const Color &aValue) = 0;

    virtual Color defaultValue() const = 0;

    virtual void addListener(Listener * aListener) = 0;

    virtual void removeListener(Listener * aListener) = 0;
};

} // namespace ds
