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

#include "core/INodeFactory.h"

namespace us {

/**
 * INodeFactory implementation that combines multiple INodeFactory implementations
 * provided at construction time.
 */
class AggregateNodeFactory : public INodeFactory, public INodeFactory::Listener
{
public:
    AggregateNodeFactory();

    virtual ~AggregateNodeFactory();

    /**
     * @copyDoc INodeFactory::create
     */
    INode *create(IProductConfiguration *aConfiguration,
                  const std::string &aType,
                  const std::string &aID,
                  const ExtensionProviders &aExtensionProviders,
                  const NodePosition &aPosition) const override;

    INodeDefinition *definition(const std::string &aType) const override;

    /**
     * @copyDoc INodeFactory::availableNodes
     */
    std::vector<std::string> availableNodes() const override;
    /**
     * @copyDoc INodeFactory::hasDefinitionForType
     */
    bool hasDefinitionForType(const std::string &aType) const override;
    /**
     * @copyDoc ::INodeFactory::addListener
     */
    void addListener(INodeFactory::Listener *aListener) override;
    /**
     * @copyDoc ::INodeFactory::removeListener
     */
    void removeListener(INodeFactory::Listener *aListener) override;
    /**
     * @copyDoc ::INodeFactory::onAvailableNodesChanged
     */
    void onAvailableNodesChanged(INodeFactory *aFactory) override;
    /**
     * Adds the given factory to this AggregateNodeFactory
     */
    void add(std::shared_ptr<INodeFactory> aFactory);
    /**
     * Removes the given factory from this AggregateNodeFactory
     */
    void remove(std::shared_ptr<INodeFactory> aFactory);

private:
    std::unordered_set<std::shared_ptr<INodeFactory>> _factories;

    std::unordered_set<INodeFactory::Listener *> _listeners;

    std::unordered_map<std::string, INodeFactory *> _typeMap;
};

} // namespace us
