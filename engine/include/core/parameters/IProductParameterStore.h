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

#include <string>

namespace us {

class IProductParameter;
class IBooleanParameter;
class IIntegerParameter;
class INumberParameter;
class IStringParameter;
class IURIParameter;
class IEnumParameter;
class ITriggerParameter;
class IColorParameter;

/**
 * Class where nodes can register as parameters. Re-implement this
 * interface depending on the platform you are running unsung on,
 * whether it is a desktop application, a webassembly build,...
 */
class IProductParameterStore
{
public:
    virtual ~IProductParameterStore();

    /**
     * Registers the given parameter.
     * @note the IProductParameterStore does not take ownership
     *       of the given output. It is the caller's responsibility
     *       to remove the parameter before it is destroyed.
     */
    virtual void addParameter(IProductParameter * aParameter) = 0;
    /**
     * Removes the given parameter.
     */
    virtual void removeParameter(IProductParameter * aParameter) = 0;

    virtual IBooleanParameter *boolean(const std::string &aID) const = 0;

    virtual IIntegerParameter *integer(const std::string &aID) const = 0;

    virtual INumberParameter *number(const std::string &aID) const = 0;

    virtual IStringParameter *string(const std::string &aID) const = 0;

    virtual IURIParameter *uri(const std::string &aID) const = 0;

    virtual IEnumParameter *enumeration(const std::string &aID) const = 0;

    virtual ITriggerParameter *trigger(const std::string &aID) const = 0;

    virtual IColorParameter *color(const std::string &aID) const = 0;
};

} // namespace us
