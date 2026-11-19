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

#include "INode.h"
#include "IProductConfiguration.h"
#include <string>
#include <vector>

namespace us {
/**
 * Interface for a factory that creates INodes
 */
class INodeFactory
{
public:
    class Listener
    {
    public:
        virtual void onAvailableNodesChanged(INodeFactory *aFactory);
    };

    virtual ~INodeFactory();

    /**
     * Creates a new INode of given type
     * @param aConfiguration The product configuration. This object exposes all cross-product
     *                       functionality that individual INodes are allowed to use.
     * @param aType Type of the new INode
     * @param aID ID of the new INode
     */
    virtual INode *create(IProductConfiguration *aConfiguration,
                          const std::string &aType,
                          const std::string &aID,
                          const ExtensionProviders &aExtensionProviders,
                          const NodePosition &aPosition) const
        = 0;

    /**
     * Returns a list with all INode types this INodeFactory supports.
     */
    virtual std::vector<std::string> availableNodes() const = 0;

    virtual INodeDefinition *definition(const std::string &aType) const = 0;

    /**
     * Returns whether this node factory can create a node of given type
     */
    virtual bool hasDefinitionForType(const std::string &aType) const = 0;

    virtual void addListener(Listener *aListener) = 0;

    virtual void removeListener(Listener *aListener) = 0;
};

} // namespace us
