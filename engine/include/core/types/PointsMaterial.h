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

#include "core/types/Color.h"
#include <string>

namespace us {

class PointsMaterial
{
public:
    PointsMaterial();

    Color &color();

    Color color() const;

    float &pointSize();

    float pointSize() const;

    float &opacity();

    float opacity() const;

    bool shaded() const;

    bool &shaded();

    bool operator==(const PointsMaterial &aOther) const;

    std::string toString() const;

    static PointsMaterial fromString(const std::string &aString);

private:
    Color _color;

    float _pointSize;

    float _opacity;

    bool _shaded;
};

} // namespace us
