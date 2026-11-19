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

#include <functional>

namespace us {

class IBooleanParameter : public IProductParameter
{
public:

    class Listener {
    public:
        virtual void onValueChanged(IBooleanParameter * aParameter, bool aValue) = 0;
        virtual void onDisplayNameChanged(IBooleanParameter *aParameter, const std::string &aName)
            = 0;
        virtual void onDefaultValueChanged(IBooleanParameter *aParameter, bool aValue) = 0;
        virtual void onVisibleChanged(IBooleanParameter *aParameter, bool aVisible) = 0;
        virtual void onEditableChanged(IBooleanParameter *aParameter, bool aEditable) = 0;
        virtual void onExternalIDChanged(IBooleanParameter *aParameter, std::string aExternalID) = 0;
        virtual void onDescriptionChanged(IBooleanParameter *aParameter, std::string aDescription)
            = 0;
    };

    virtual ~IBooleanParameter();

    virtual bool value() const = 0;

    virtual bool setValue(bool aValue) = 0;

    virtual bool defaultValue() const = 0;

    virtual void addListener(Listener * aListener) = 0;

    virtual void removeListener(Listener * aListener) = 0;

};

} // namespace us
