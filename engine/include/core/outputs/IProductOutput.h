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

#include <cstdint>
#include <string>

namespace us {

class IProductOutputVisitor;

/**
 * Interface for a product output.
 */
class IProductOutput {

public:

    virtual ~IProductOutput();

    virtual std::string id() const = 0;
    virtual std::string pass() const = 0;
    /**
     * Identifies the output across passes: "<pass>/<id>"
     */
    std::string key() const;
    virtual bool visible() const = 0;
    virtual std::string displayName() const = 0;
    virtual std::string description() const = 0;
    virtual std::string externalID() const = 0;

    virtual void accept(IProductOutputVisitor *aVisitor) = 0;
};

/**
 * Returns a new process-unique id for the geometries and materials that mesh
 * and polyline outputs publish (see IMeshProductOutput::Listener). An id
 * stands for whatever its latest content is.
 */
std::uint64_t newResourceID();

} // namespace us
