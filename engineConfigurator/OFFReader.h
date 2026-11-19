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

/**
 * Reader for the OFF mesh format
 */
class OFFReader : public us::ITypeReader
{
public:
    OFFReader() = default;

    virtual ~OFFReader() = default;
    ///returns the type read by this reader
    std::type_index type() const override;
    ///returns the list of extensions this reader can process
    std::vector<std::string> formats() const override;
    ///parses the OFF stream
    us::Any read(std::istream &aIn) const override;
};

