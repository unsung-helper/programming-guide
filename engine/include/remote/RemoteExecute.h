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

#include "core/Product_p.h"
#include <string>

namespace us {

class IProductConfiguration;
class INodeFactory;

class RemoteExecute
{
public:
    RemoteExecute(std::unique_ptr<Product> &&aProduct);

    std::pair<std::string, bool> execute(const std::string &aBody);

private:
    std::unique_ptr<Product> _product;
};

} // namespace us
