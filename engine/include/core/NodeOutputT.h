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

#include "NodeOutput.h"

namespace us {

/**
 * Template extension of NodeOutput. The template parameter defines the type of this output.
 */
template<class T>
class NodeOutputT : public NodeOutput
{
public:
    /**
     * Creates a new NodeOutputT with given node, name and description
     */
    NodeOutputT(INode *aNode,
                std::string aName,
                std::string aDescription,
                Any aConstantValue = Any())
        : NodeOutput(aNode, aName, aDescription, typeid(T), aConstantValue)
    {}
};

} // namespace us
