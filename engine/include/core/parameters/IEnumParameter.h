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
#include "core/EnumerationType.h"

namespace us {

class IEnumParameter : public us::IProductParameter
{
public:
    enum class ParameterPresentation { DropDown, Tiles };

    enum class OptionPresentation { Label, Icon, Both };

    class Listener
    {
    public:
        virtual void onValueChanged(IEnumParameter *aParameter,
                                    const EnumerationType::Option &aValue)
            = 0;
        virtual void onDisplayNameChanged(IEnumParameter *aParameter, const std::string &aName) = 0;

        virtual void onDefaultValueChanged(IEnumParameter *aParameter,
                                           const EnumerationType::Option &aValue)
            = 0;
        virtual void onVisibleChanged(IEnumParameter *aParameter, bool aVisible) = 0;
        virtual void onEditableChanged(IEnumParameter *aParameter, bool aEditable) = 0;
        virtual void onExternalIDChanged(IEnumParameter *aParameter, std::string aExternalID) = 0;
        virtual void onDescriptionChanged(IEnumParameter *aParameter, std::string aDescription) = 0;
        virtual void onOptionsChanged(IEnumParameter *aParameter,
                                      std::vector<std::pair<EnumerationType::Option, URI>> aOptions)
            = 0;
        virtual void onParameterPresentationChanged(IEnumParameter *aParameter,
                                                    ParameterPresentation aPresentation)
            = 0;
        virtual void onOptionPresentationChanged(IEnumParameter *aParameter,
                                                 OptionPresentation aPresentation)
            = 0;
    };

    virtual ~IEnumParameter();

    virtual EnumerationType::Option value() const = 0;

    virtual std::vector<std::pair<EnumerationType::Option, URI>> options() const = 0;

    virtual bool setValue(const EnumerationType::Option &aValue) = 0;

    virtual EnumerationType::Option defaultValue() const = 0;

    virtual ParameterPresentation parameterPresentation() const = 0;

    virtual OptionPresentation optionPresentation() const = 0;

    virtual void addListener(Listener *aListener) = 0;

    virtual void removeListener(Listener *aListener) = 0;
};

} // namespace us
