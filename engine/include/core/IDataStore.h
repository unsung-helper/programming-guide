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

#include "types/URI.h"
#include <iostream>
#include <unordered_set>

namespace us {

class IDataStore
{
public:
    virtual ~IDataStore();

    virtual std::unordered_set<std::string> protocols() const = 0;

    virtual bool readable() const = 0;

    virtual bool writable() const = 0;

    virtual bool read(const URI &aUri, std::ostream &aContents) = 0;

    virtual bool write(const URI &aUri, std::istream &aContents) = 0;
};

} // namespace us
