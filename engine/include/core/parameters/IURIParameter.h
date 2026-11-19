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
#include "core/types/URI.h"
#include <vector>

namespace us {

class IURIParameter : public us::IProductParameter
{
public:

    class Listener {
    public:
        virtual void onValueChanged(IURIParameter *aParameter, const URI &aValue) = 0;
        virtual void onDisplayNameChanged(IURIParameter *aParameter, const std::string &aName) = 0;
        virtual void onDefaultValueChanged(IURIParameter *aParameter, const URI &aValue) = 0;
        virtual void onVisibleChanged(IURIParameter *aParameter, bool aVisible) = 0;
        virtual void onEditableChanged(IURIParameter *aParameter, bool aEditable) = 0;
        virtual void onExternalIDChanged(IURIParameter *aParameter, std::string aExternalID) = 0;
        virtual void onDescriptionChanged(IURIParameter *aParameter, std::string aDescription) = 0;
    };

    virtual ~IURIParameter();

    virtual URI value() const = 0;

    virtual bool setValue(const URI &aValue) = 0;

    virtual URI defaultValue() const = 0;

    virtual std::vector<std::string> extensions() = 0;

    virtual std::vector<std::string> protocols() = 0;

    virtual void addListener(Listener *aListener) = 0;

    virtual void removeListener(Listener * aListener) = 0;

};

} // namespace us
