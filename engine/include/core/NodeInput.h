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

#include "INodeInputInternal.h"

#include "util/OrderedSet.h"

#include "INodeOutput.h"
#include <vector>

namespace us {

/**
 * Default implementation of INodeInputInternal. Moreover it implements INodeOutput::listener
 * to be aware of state changes of its connected output.
 */
class NodeInput : public INodeInputInternal, public INodeOutput::Listener
{
public:
    /**
     * Creates a new NodeInput with given node, name, description and type
     */
    NodeInput(INode *aNode,
              std::string aName,
              std::string aDescription,
              bool aCanConnect,
              std::type_index aType = typeid(void));

    ~NodeInput();
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
     * @copydoc INodeInput::state
     */
    State state(const Pass &aPass) const override;
    /**
     * @copydoc INodeInput::connect
     */
    void connect(INodeOutput *aOutput) override;
    /**
     * @copydoc INodeInput::disconnect
     */
    void disconnect() override;
    /**
     * @copydoc INodeInput::connection
     */
    INodeOutput *connection() const override;
    /**
     * @copydoc INodeInput::value
     */
    Any value(const Pass &aPass) const override;

    /**
     * @copydoc INodeInput::setFallbackValue
     */
    void setFallbackValue(const Any &aValue) override;
    /**
     * @copydoc INodeInput::fallbackValue
     */
    Any fallbackValue() const override;
    /**
     * Sets the state to Accepted
     */
    void accept(const Pass &aPass);
    void acceptFallback();

    /**
     * @copydoc INodeInput::addListener
     */
    void addListener(INodeInput::Listener *aListener) override;
    /**
     * @copydoc INodeInput::removeListener
     */
    void removeListener(INodeInput::Listener *aListener) override;

    /**
     * @copydoc INodeOutput::Listener::onStateChanged
     */
    void onStateChanged(INodeOutput *aOutput,
                        INodeOutput::State aState,
                        const Pass &aPass) override;

    bool canConnect() const override;

    void addPass(const Pass &aPass) override;

    void removePass(const Pass &aPass) override;

    const std::unordered_set<Any> &options() const override;

    void addOption(Any aOption);

    void removeOption(Any aOption);
    /**
     * Replaces all options at once. The fallback value is kept when it
     * is still one of the given options, otherwise it becomes the first
     * given option. Listeners are notified of the option change once.
     */
    void setOptions(const std::vector<Any> &aOptions);

    void onGroupsChanged(INodeOutput *aOutput) override;

    PassesGroups groups() const override;

private:
    void updateRetrieveValue();

    void setState(const Pass &aPass, State aState);

    void invalidateAll();

    bool hasPass(const Pass &aPass) const;

    INode *_node;

    std::string _name;

    std::string _description;

    std::type_index _type;

    Any _fallbackValue;

    INodeOutput * _connection;

    OrderedSet<INodeInput::Listener *> _listeners;

    bool _canConnect;

    std::unordered_map<std::string, State> _states;

    std::unordered_set<Any> _options;

    using RetrieveValue = std::function<Any(const Pass &aPass)>;
    RetrieveValue _retrieveValue;
};

} // namespace us
