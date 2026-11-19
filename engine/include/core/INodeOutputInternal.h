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

#include "INodeOutput.h"

namespace us {

/**
 * This class extends INodeOutput with methods that should
 * only be available to INode and its extensions.
 */
class INodeOutputInternal : public INodeOutput
{
public:

    virtual ~INodeOutputInternal();

    /**
     * Invalidates this output
     */
    virtual void invalidate(const Pass &aPass) = 0;
    /**
     * Clears the value of this output, releasing the memory it holds
     */
    virtual void release(const Pass &aPass) = 0;
    /**
     * Invalidates all passes
     */
    virtual void invalidateAll() = 0;
    /**
     * Releases all passes
     */
    virtual void releaseAll() = 0;

    /**
     * Updates the value and changes the state to Available.
     * Behavior is undefined when the given value has inappropriate type.
     */
    virtual void setValue(const Pass &aPass, Any aValue) = 0;
    /**
     * Adds given pass
     */
    virtual void addPass(const Pass &aPass) = 0;
    /**
     * Removes given pass
     */
    virtual void removePass(const Pass &aPass) = 0;
    /**
     * Sets this output's PassesGroups partitioning.
     */
    virtual void setGroups(const PassesGroups &aGroups) = 0;
};

} // namespace us
