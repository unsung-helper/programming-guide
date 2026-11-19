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

class IStringParameter : public us::IProductParameter
{
public:

    class Listener {
    public:
        virtual void onValueChanged(IStringParameter * aParameter, const std::string & aValue) = 0;
        virtual void onDisplayNameChanged(IStringParameter *aParameter, const std::string &aName) = 0;
        virtual void onDefaultValueChanged(IStringParameter *aParameter, const std::string &aValue)
            = 0;
        virtual void onVisibleChanged(IStringParameter *aParameter, bool aVisible) = 0;
        virtual void onEditableChanged(IStringParameter *aParameter, bool aEditable) = 0;
        virtual void onExternalIDChanged(IStringParameter *aParameter, std::string aExternalID) = 0;
        virtual void onDescriptionChanged(IStringParameter *aParameter, std::string aDescription) = 0;
    };

    virtual ~IStringParameter();

    virtual std::string value() const = 0;

    virtual std::string defaultValue() const = 0;

    virtual bool setValue(const std::string &aValue) = 0;

    virtual void addListener(Listener * aListener) = 0;

    virtual void removeListener(Listener * aListener) = 0;

};

} // namespace us
