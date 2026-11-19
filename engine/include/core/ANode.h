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
#include "INode.h"
#include "core/INodeConnector.h"
#include "core/Pass.h"
#include "util/OrderedSet.h"
#include <memory>
#include <string>

namespace us {

class INodeOutputInternal;
class INodeInputInternal;
class ANodeExtension;
class ANode;

class ANodeDefinition : public INodeDefinition
{
public:
    ANodeDefinition(const std::string &aUserFriendlyName, const std::set<Category> &aCategories);

    virtual ~ANodeDefinition() = default;
    /**
     * @copydoc INodeDefinition::instances
     */
    std::unordered_set<INode *> instances() const override;
    /**
     * @copydoc INodeDefinition::categories
     */
    std::set<Category> categories() const override;
    /**
     * @copydoc INodeDefinition::userFriendlyName
     */
    std::string userFriendlyName() const override;
    /**
     * @copydoc INodeDefinition::addListener
     */
    void addListener(Listener *aListener) override;
    /**
     * @copydoc INodeDefinition::removeListener
     */
    void removeListener(Listener *aListener) override;
    /**
     * Sets the user friendly name
     */
    void setUserFriendlyName(const std::string &aName);

private:
    friend class ANode;

    void addInstance(INode *aNode);

    void removeInstance(INode *aNode);

    std::unordered_set<INode *> _instances;

    std::string _userFriendlyName;

    std::set<Category> _categories;

    OrderedSet<INodeDefinition::Listener *> _listeners;
};

/**
 * Abstract implementation of INode that manages most common dependency related use cases.
 * It also supports node extensions.
 */
class ANode : public INode
{
public:
    ANode(ANodeDefinition *aDefinition,
          IProductConfiguration *aConfiguration,
          const std::string &aID,
          const ExtensionProviders &aExtensionProviders,
          NodePosition aPosition);

    virtual ~ANode();

    /**
     * @copydoc INode::definition
     */
    INodeDefinition *definition() const override;
    /**
     * @copydoc INode::id
     */
    std::string id() const override final;
    /**
     * @copydoc INode::inputs
     */
    std::vector<std::string> inputs() const override final;
    /**
     * @copydoc INode::outputs
     */
    std::vector<std::string> outputs() const override final;
    /**
     * @copydoc INode::input
     */
    INodeInput * input(const std::string & aInput) override final;
    /**
     * @copydoc INode::output
     */
    INodeOutput * output(const std::string & aOutput) override final;
    /**
     * @copydoc INode::getDependencies
     */
    std::vector<INodeOutput *> getDependencies() const override final;
    /**
     * @copydoc INode::getDependents
     */
    std::vector<INodeInput *> getDependents() const override final;
    /**
     * @copydoc INode::requiredDependencies
     */
    std::vector<INodeOutput *> requiredDependencies(Target aTarget,
                                                    const Pass &aPass) override;
    /**
     * @copydoc INode::userFriendlyName
     */
    std::string userFriendlyName() const override final;
    /**
     * @copydoc INode::setUserFriendlyName
     */
    void setUserFriendlyName(const std::string &aName) override final;
    /**
     * @copydoc INode::addListener
     */
    void addListener(Listener *aListener) override;
    /**
     * @copydoc INode::removeListener
     */
    void removeListener(Listener *aListener) override;
    /**
     * @copydoc INode::execute
     */
    void execute(Target aTarget, const Pass &aPass) override final;
    /**
     * @copydoc INode::configuration
     */
    IProductConfiguration *configuration() const override;
    /**
     * @copydoc INode::logs
     */
    const Logs &logs() const override;
    /**
     * @copydoc INode::clearLogs
     */
    void clearLogs() override;
    /**
     * @copydoc INode::moveTo
     */
    void moveTo(const NodePosition &aPosition) override;
    /**
     * @copydoc INode::position
     */
    NodePosition position() const override;
    /**
     * @copydoc INode::save
     */
    void save(IDataDocument &aConfiguration) override;
    /**
     * @copydoc INode::load
     */
    void load(IDataDocument &aConfiguration) override;

protected:

    /**
     * Registers the given input of the ANode subclass.
     * @note the subclass is responsible for a proper
     * cleanup of the given input upon destruction.
     * Make sure to unregister the input beforehand.
     */
    void registerInput(us::INodeInputInternal *aInput, bool aCausesInvalidation = true);
    /**
     * Registers the given output of the ANode subclass.
     * @note the subclass is responsible for a proper
     * cleanup of the given output upon destruction.
     * Make sure to unregister the output beforehand.
     */
    void registerOutput(INodeOutputInternal * aOutput);
    /**
     * Unregisters the given input.
     */
    void unregisterInput(us::INodeInputInternal *aInput);
    /**
     * Unregisters the given output.
     */
    void unregisterOutput(INodeOutputInternal * aOutput);
    /**
     * The actual implementation of the node.
     */
    virtual void executeImpl(Target aTarget, const Pass &aPass);
    /**
     * Logs the given message
     */
    void log(Logs::Level aLevel, const Pass &aPass, const std::string &aMessage);
    /**
     * Called when a pass is being added
     */
    virtual void onBeginAddPass(const Pass &aPass);
    /**
     * Called when a pass has been added.
     */
    virtual void onEndAddPass(const Pass &aPass);
    /**
     * Called when a pass is being removed
     */
    virtual void onBeginRemovePass(const Pass &aPass);
    /**
     * Called when a pass has been removed
     */
    virtual void onEndRemovePass(const Pass &aPass);
    /**
     * Returns the partitioning of this node: PassesGroup holds
     * passes that will receive identical node inputs.
     */
    virtual PassesGroups partitionGroups() const;
    /**
     * Returns the listeners of this node
     */
    const OrderedSet<INode::Listener *> &listeners() const;

private:

    class ANodePrivate;
    std::unique_ptr<ANodePrivate> _d;
};

} // namespace us
