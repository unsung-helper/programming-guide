/*
 * Copyright (c) 2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */
#pragma once

#include "Color.h"
#include "Vec3.h"

namespace us {

class PointLight
{
public:
    Vec3 _position{0, 0, 0};

    Color _color{1.0, 1.0, 1.0};

    bool _enabled{true};

    bool _castsShadow{false};
};

} // namespace ds
