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

#include "Any.h"
#include <iostream>
#include <string>
#include <vector>

namespace us {

class ITypeReader
{
public:
    virtual ~ITypeReader();

    virtual std::type_index type() const = 0;

    virtual std::vector<std::string> formats() const = 0;

    virtual Any read(std::istream &aIn) const = 0;
};

} // namespace us
