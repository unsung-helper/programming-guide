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
#include "IParameterVisitor.h"

namespace us {


/**
 * Interfaces for parameters
 */
class IProductParameter {

public:

    virtual ~IProductParameter();

    /**
     * Returns the ID of the parameter
     */
    virtual std::string id() const = 0;
    /**
     * Returns the user-friendly name of the parameter
     */
    virtual std::string displayName() const = 0;
    /**
     * Returns whether the parameter is visible or not
     */
    virtual bool visible() const = 0;
    /**
     * Returns whether the parameter is editable or not
     */
    virtual bool editable() const = 0;
    /**
     * Returns the ID with which the parameter can be identified
     * by external applications.
     */
    virtual std::string externalID() const = 0;
    /**
     * Returns a short description about the parameter
     */
    virtual std::string description() const = 0;

    /**
     * Accepts the given visitor
     */
    virtual void accept(IParameterVisitor * aVisitor) = 0;

};

} // namespace us
