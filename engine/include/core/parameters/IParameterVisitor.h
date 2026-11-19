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

namespace us {

class IBooleanParameter;
class IIntegerParameter;
class INumberParameter;
class IStringParameter;
class IURIParameter;
class IEnumParameter;
class ITriggerParameter;
class IColorParameter;

class IParameterVisitor
{
public:
    virtual ~IParameterVisitor();

    virtual void visit(IBooleanParameter * aParameter) = 0;
    virtual void visit(IIntegerParameter * aParameter) = 0;
    virtual void visit(INumberParameter * aParameter) = 0;
    virtual void visit(IStringParameter * aParameter) = 0;
    virtual void visit(IURIParameter * aParameter) = 0;
    virtual void visit(IEnumParameter *aParameter) = 0;
    virtual void visit(ITriggerParameter *aParameter) = 0;
    virtual void visit(IColorParameter *aParameter) = 0;
};

} // namespace us
