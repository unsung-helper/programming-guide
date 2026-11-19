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

#include <iostream>
#include <unordered_map>

namespace us {

class Rest
{
public:
    bool get(const std::string &aEndpoint,
             std::ostream &aOut,
             const std::unordered_map<std::string, std::string> &aHeaders = {}) const;

    bool post(const std::string &aEndpoint,
              const std::string &aBody,
              std::ostream &aOut,
              const std::unordered_map<std::string, std::string> &aHeaders = {}) const;

    bool put(const std::string &aEndpoint,
             const std::string &aBody,
             std::ostream &aOut,
             const std::unordered_map<std::string, std::string> &aHeaders = {}) const;
};

} // namespace us
