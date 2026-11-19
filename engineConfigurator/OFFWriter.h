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

class OFFWriter : public us::ITypeWriter
{
public:
    OFFWriter() = default;

    virtual ~OFFWriter() = default;

    ///returns the data type this writer can process
    std::type_index type() const override;
    ///returns the file format this writer writes
    std::string format() const override;
    ///writes the data to a stream in this file format
    void write(const us::Any &aAsset, std::ostream &aOut) const override;
};

