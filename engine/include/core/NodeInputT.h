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

#include "NodeInput.h"

namespace us {

/**
 * Template extension of NodeInput. The template parameter defines the type of this input.
 */
template<class T>
class NodeInputT : public NodeInput
{
public:
    /**
     * Creates a new NodeInputT with given node, name and description
     */
    NodeInputT(INode *aNode, std::string aName, std::string aDescription, bool aCanConnect = true)
        : NodeInput(aNode, aName, aDescription, aCanConnect, typeid(T))
    {}

    /**
     * Shorthand method that retrieves the current
     * value, casts it to the correct type and
     * sets the status to accepted.
     */
    T acceptValue(const Pass &aPass)
    {
        auto result = value(aPass).template get<T>();
        accept(aPass);
        return result;
    }

    T acceptFallbackValue()
    {
        auto result = fallbackValue().template get<T>();
        acceptFallback();
        return result;
    }
};

} // namespace us
