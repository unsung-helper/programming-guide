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

#include "ANodeExtension.h"
#include "INodeFactory.h"
#include "core/INode.h"
#include <functional>
#include <unordered_map>

namespace us {

/**
 * Implementation of INodeFactory that allows to register lambda functions to create
 * specific INodes.
 */
class NodeFactory : public us::INodeFactory, public INodeDefinition::Listener
{
public:
    // /// Callback to create a specific INode
    // using Creator = std::function< INode *(IProductConfiguration *,const std::string &, NodeExtensionList &&aExtensions)>;

    NodeFactory() = default;
    virtual ~NodeFactory() = default;
    NodeFactory(NodeFactory && aOther) = default;
    NodeFactory & operator = (const NodeFactory & aOther) = default;
    NodeFactory & operator = (NodeFactory && aOther) = default;

    void registerDefinition(std::unique_ptr<INodeDefinition> &&aDefinition);

    void unregisterDefinition(const std::string &aType);

    /**
     * Creates a node of given type with given id, for the given product configuration,
     * or nullptr if the type is not available.
     */
    INode *create(IProductConfiguration *aConfiguration,
                  const std::string &aType,
                  const std::string &aID,
                  const ExtensionProviders &aExtensionProviders,
                  const NodePosition &aPosition) const override;

    INodeDefinition *definition(const std::string &aType) const override;

    /**
     * @copydoc INodeFactory::availableNodes
     */
    std::vector<std::string> availableNodes() const override;

    /**
     * @copydoc INodeFactory::hasDefinitionForType
     */
    bool hasDefinitionForType(const std::string &aType) const override;

    /**
     * @copydoc INodeFactory::addListener
     */
    void addListener(INodeFactory::Listener *aListener) override;
    /**
     * @copydoc INodeFactory::removeListener
     */
    void removeListener(INodeFactory::Listener *aListener) override;

    void onUserFriendlyNameChanged(INodeDefinition *aDefinition) override;

private:
    std::unordered_map<std::string, std::unique_ptr<INodeDefinition>> _creators;

    std::unordered_set<INodeFactory::Listener *> _listeners;
};

} // namespace us
