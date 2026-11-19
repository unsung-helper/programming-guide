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

#include "stb_image.h"
#include <array>
#include <cstdint>
#include <memory>
#include <vector>

namespace us {

class Image
{
public:
    using Pixel = std::array<uint8_t, 4>;
    Image();
    int _width;
    int _height;
    //data, in row-major order, top-to-bottom
    std::vector<Pixel> _data;
};

using ImagePtr = std::shared_ptr<Image>;

} // namespace us
