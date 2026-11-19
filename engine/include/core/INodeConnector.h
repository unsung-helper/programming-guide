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

#include <string>
#include <typeindex>

namespace us {

class INode;

/**
 * Base class for in- and outputs in the graph, holding
 * common properties such as name, description and type.
 */
class INodeConnector
{
public:

    virtual ~INodeConnector();

    /**
     * Returns the node this connector belongs to.
     */
    virtual INode *node() const = 0;
    /**
     * Returns the name of this connector
     */
    virtual const std::string & name() const = 0;
    /**
     * Returns the description of this connector.
     */
    virtual const std::string & description() const = 0;
    /**
     * Returns the type of this connector
     */
    virtual std::type_index type() const = 0;
};

} // namespace us

