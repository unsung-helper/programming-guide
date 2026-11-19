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

#include "core/ITypeWriter.h"

namespace us {

class PNGWriter : public us::ITypeWriter
{
public:
    PNGWriter() = default;

    virtual ~PNGWriter() = default;

    std::type_index type() const override;

    std::string format() const override;

    void write(const us::Any &aAsset, std::ostream &aOut) const override;
};

} // namespace us
