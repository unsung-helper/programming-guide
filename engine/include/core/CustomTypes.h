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

#include "core/Any.h"
#include <functional>
#include <string>
#include <tuple>
#include <typeindex>
#include <vector>

namespace us {

using CustomType = std::tuple<std::type_index, std::string, Any>;

using CustomConversion
    = std::tuple<std::type_index, std::type_index, std::function<Any(const Any &)>>;

using CustomTypes = std::vector<CustomType>;

using CustomConversions = std::vector<CustomConversion>;

} // namespace us
