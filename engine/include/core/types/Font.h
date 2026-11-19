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

#include "core/types/Buffer.h"
#include <memory>

namespace us {

class Font;

using FontPtr = std::shared_ptr<Font>;

class Font
{
public:
    Font();

    Font(const Buffer &aBuffer);

    ~Font() = default;

    Buffer _contents;
};

} // namespace us
