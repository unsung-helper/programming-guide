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

#include "nlohmann/json.hpp"

namespace us {

class Form;

using FormPtr = std::shared_ptr<Form>;

class Form
{
public:
    Form();

    ~Form() = default;

    static FormPtr fromString(const std::string &aContentsString);

    std::string toString() const;

    nlohmann::json _contents;
};

} // namespace us
