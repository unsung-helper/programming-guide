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

class ITriggerParameter : public IProductParameter
{
public:

    class Listener {
    public:
        virtual void onDisplayNameChanged(ITriggerParameter *aParameter, const std::string &aName)
            = 0;
        virtual void onVisibleChanged(ITriggerParameter *aParameter, bool aVisible) = 0;
        virtual void onEditableChanged(ITriggerParameter *aParameter, bool aEditable) = 0;
        virtual void onExternalIDChanged(ITriggerParameter *aParameter, std::string aExternalID) = 0;
        virtual void onDescriptionChanged(ITriggerParameter *aParameter, std::string aDescription)
            = 0;
        virtual void onTriggered(ITriggerParameter *aParameter) = 0;
    };

    virtual ~ITriggerParameter();

    virtual bool trigger() = 0;

    virtual void addListener(Listener * aListener) = 0;

    virtual void removeListener(Listener * aListener) = 0;
};

} // namespace us
