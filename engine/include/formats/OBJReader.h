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

#include "core/ITypeReader.h"

namespace us {

class OBJReader : public us::ITypeReader
{
public:
    OBJReader() = default;

    virtual ~OBJReader() = default;

    std::type_index type() const override;

    std::vector<std::string> formats() const override;

    Any read(std::istream &aIn) const override;
};

} // namespace us
