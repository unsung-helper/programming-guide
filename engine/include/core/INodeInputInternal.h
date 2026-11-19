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

#include "core/INodeInput.h"

namespace us {

/**
 * This class extends INodeInput with methods that should
 * only be available to INode and its extensions.
 */
class INodeInputInternal : public us::INodeInput
{
public:

    virtual ~INodeInputInternal();

    virtual void addPass(const Pass &aPass) = 0;

    virtual void removePass(const Pass &aPass) = 0;
};

} // namespace us
