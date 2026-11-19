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

#include "INodeOutputInternal.h"
#include <unordered_set>

#include "INode.h"
#include "INodeInput.h"
#include "util/OrderedSet.h"

namespace us {

/**
 * Default implementation of INodeOutputInternal. 
 */
class NodeOutput : public INodeOutputInternal
{
public:
    /**
     * Creates a new NodeOutput with given node, name, description and type
     */
    NodeOutput(INode *aNode,
               std::string aName,
               std::string aDescription,
               std::type_index aType,
               Any aConstantValue = Any());

    ~NodeOutput();
    /**
     * @copydoc INodeConnector::node
     */
    INode *node() const override;
    /**
     * @copydoc INodeConnector::name
     */
    const std::string &name() const override;
    /**
     * @copydoc INodeConnector::description
     */
    const std::string &description() const override;
    /**
     * @copydoc INodeConnector::type
     */
    std::type_index type() const override;
    /**
     * @copydoc INodeOutput::state
     */
    State state(const Pass &aPass) const override;
    /**
     * @copydoc INodeOutput::connect
     */
    void connect(INodeInput *aInput) override;
    /**
     * @copydoc INodeOutput::disconnect
     */
    void disconnect(INodeInput *aInput) override;
    void disconnect() override;
    /**
     * @copydoc INodeOutput::connections
     */
    std::vector<INodeInput *> connections() const override;
    /**
     * @copydoc INodeOutput::hasConnectionWith
     */
    bool hasConnectionWith(INodeInput *aInput) const override;
    /**
     * @copydoc INodeOutput::value
     */
    Any value(const Pass &aPass) const override;
    /**
     * @copydoc INodeOutputInternal::setValue
     */
    void setValue(const Pass &aPass, Any aValue) override;
    /**
     * @copydoc INodeOutputInternal::invalidate
     */
    void invalidate(const Pass &aPass) override;
    /**
     * @copydoc INodeOutputInternal::release
     */
    void release(const Pass &aPass) override;
    /**
     * @copydoc INodeOutput::addListener
     */
    void addListener(INodeOutput::Listener *aListener) override;
    /**
     * @copydoc INodeOutput::removeListener
     */
    void removeListener(INodeOutput::Listener *aListener) override;

    bool constant() const override;

    Any constantValue() const override;

    void addPass(const Pass &aPass) override;

    void removePass(const Pass &aPass) override;

    void invalidateAll() override;

    void releaseAll() override;

    PassesGroups groups() const override;

    void setGroups(const PassesGroups &aGroups) override;

private:
    void setState(const Pass &aPass, State aState);

    bool hasPass(const Pass &aPass) const;

    std::unordered_set<INodeInput *> _connections;

    OrderedSet<INodeOutput::Listener *> _listeners;

    INode * _node;

    std::string _name;

    std::string _description;

    std::type_index _type;

    std::unordered_map<std::string, std::tuple<State, Any>> _rep;

    Any _constant;

    PassesGroups _groups;
};

} // namespace us
