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

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace us {

class Table
{
public:
    Table(const std::vector<std::string> &aHeaders, std::vector<std::vector<std::string>> &aValues);

    const std::vector<std::string> _headers;
    std::vector<std::vector<std::string>> _values;
};

using TablePtr = std::shared_ptr<Table>;

} // namespace us
