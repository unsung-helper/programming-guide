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

#include <functional>

namespace us {

class Finally
{
public:
    Finally(std::function<void()> aCleanup);

    ~Finally();

private:
    std::function<void()> _cleanUp;
};

} // namespace us
