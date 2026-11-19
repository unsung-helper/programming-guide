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

#include "IProductOutput.h"

namespace us {

/**
 * Class where nodes can register as outputs. Re-implement this
 * interface depending on the platform you are running unsung on,
 * whether it is a desktop application, a webassembly build,...
 */
class IProductOutputStore
{
public:
    virtual ~IProductOutputStore();

    /**
     * Registers the given output.
     * @note the IProductOutputStore does not take ownership
     *       of the given output. It is the caller's responsibility
     *       to remove the output before it is destroyed.
     */
    virtual void addOutput(IProductOutput * aOutput) = 0;

    /**
     * Removes the given output.
     */
    virtual void removeOutput(IProductOutput * aOutput) = 0;


};

} // namespace us
