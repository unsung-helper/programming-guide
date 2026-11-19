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

#include "Color.h"

#include <memory>
#include <vector>

namespace us {

class ColorMap
{
public:
    ColorMap();

    ColorMap(const std::vector<std::pair<float, Color>> &aSteps);

    const std::pair<float, Color> &step(int aStep) const;

    int nbSteps() const;

    Color value(float aValue) const;

private:
    std::vector<std::pair<float, Color>> _steps;
};

using ColorMapPtr = std::shared_ptr<ColorMap>;

} // namespace us
