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

#include "INodeTargets.h"
#include "Logs.h"
#include "core/Category.h"
#include "core/ExtensionProvider.h"
#include "core/Pass.h"
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

namespace us {

class INodeInput;
class INodeOutput;
class INodeConnector;
class INode;
class IProductConfiguration;
class IDataDocument;

///2D Position of the node on the graph canvas.
using NodePosition = std::pair<int, int>;

///Definition (metadata) of the node. Allows to create
///instances of the node.
class INodeDefinition
{
public:
    class Listener
    {
    public:
        ///Called whenever a node of this definition is created
        virtual void onInstanceAdded(INodeDefinition *aDefinition, INode *aNode);
        ///Called whenever a node of this definition is removed
        virtual void onInstanceRemoved(INodeDefinition *aDefinition, INode *aNode);
        ///Called whenever the definition's user friendly name changes
        virtual void onUserFriendlyNameChanged(INodeDefinition *aDefinition);
    };

    INodeDefinition() = default;

    virtual ~INodeDefinition() = default;
    /**
     * Returns the type of the INode: the unique name with which each
     * implementation of INode is identified.
     */
    virtual std::string type() const = 0;
    /**
     * Returns an explanation about what this INode implementation does.
     */
    virtual std::string description() const = 0;
    /**
     * User friendly name of the definition
     */
    virtual std::string userFriendlyName() const = 0;
    /**
     * Returns the categories this node definition belongs to.
     */
    virtual std::set<Category> categories() const = 0;
    /**
     * Creates a new node with given configuration
     */
    virtual INode *create(IProductConfiguration *aConfiguration,
                          const std::string &aID,
                          const ExtensionProviders &aExtensionProviders,
                          const NodePosition &aPosition)
        = 0;

    /**
     * Returns all current node instances of this definition
     */
    virtual std::unordered_set<INode *> instances() const = 0;
    /**
     * Adds a listener.
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the listener
     */
    virtual void removeListener(Listener *aListener) = 0;

};

/**
 * This is the base class for all nodes in the product graph. It exposes its inputs
 * and outputs. By executing it the node evaluates its inputs, makes some calculations
 * and presents the results in its outputs.
 *
 * The node also exposes its required dependencies: this is a dynamic list of inputs whose connected nodes need
 * to be executed first before this node can be executed.
 *
 * Do not store pointers to INode's in- and outputs as we cannot guarantee the lifetime of these objects.
 */
class INode
{
public:

    class Listener
    {
    public:
        virtual void onInputsChanged(INode *aNode);
        virtual void onOutputsChanged(INode *aNode);
        virtual void onUserFriendlyNameChanged(INode *aNode);
        virtual void onLogsUpdated(INode *aNode);
        virtual void onPositionChanged(INode *aNode);
    };

    INode() = default;
    /**
     * Destroys this INode
     * @note please make sure to disconnect all in- and outputs of this node
     *       before destruction to guarantee proper behavior of the product graph.
     */
    virtual ~INode() = default;
    INode(const INode & aOther) = delete;
    INode(INode && aOther) = delete;
    INode & operator = (const INode & aOther) = delete;
    INode & operator = (INode && aOther) = delete;

    virtual INodeDefinition *definition() const = 0;
    /**
     * Returns the unique id with which INode instances are identified
     * in a product.
     */
    virtual std::string id() const = 0;
    /**
     * Returns a more user friendly name for this INode instance, with
     * which it can be identified easier by designers.
     */
    virtual std::string userFriendlyName() const = 0;
    /**
     * Sets the user friendly name of this INode instance.
     */
    virtual void setUserFriendlyName(const std::string &aName) = 0;
    /**
     * Returns the names of all the inputs of this INode
     */
    virtual std::vector<std::string> inputs() const = 0;
    /**
     * Returns the names of all the outputs of this INode
     */
    virtual std::vector<std::string> outputs() const = 0;
    /**
     * Returns the input object associated with given name,
     * or nullptr if there is no such input object.
     * @note do not store this pointer as we do not guarantee the lifetime of this object
     */
    virtual INodeInput * input(const std::string & aInput) = 0;
    /**
     * Returns the output object associated with given name,
     * or nullptr if there is no such output object.
     * @note do not store this pointer as we do not guarantee the lifetime of this object
     */
    virtual INodeOutput * output(const std::string & aOutput) = 0;
    /**
     * Returns the list of output objects of other nodes with which
     * input objects of this INode are connected.
     * @note do not store these pointers as we do not guarantee their lifetimes
     */
    virtual std::vector<INodeOutput *> getDependencies() const = 0;
    /**
     * Returns the list of input objects of other nodes with which
     * output objects of this INode are connected.
     * @note do not store these pointers as we do not guarantee their lifetimes
     */
    virtual std::vector<INodeInput *> getDependents() const = 0;
    /**
     * Returns the list of dependencies whose nodes need to be executed
     * before this INode can be executed. Be aware that this list changes
     * dynamically upon changes within the product graph.
     * @note do not store these pointers as we do not guarantee their lifetimes
     */
    virtual std::vector<INodeOutput *> requiredDependencies(Target aTarget, const Pass &aPass) = 0;
    /**
     * Executes this INode. This method can only be run successfully
     * when the list of required dependencies is empty. If not its
     * behavior is undefined.
     */
    virtual void execute(Target aTarget, const Pass &aPass) = 0;
    /**
     * Moves this node to the given position
     */
    virtual void moveTo(const NodePosition &aPosition) = 0;
    /**
     * The position of this node on the canvas
     */
    virtual NodePosition position() const = 0;
    /**
     * Adds a listener
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the listener
     */
    virtual void removeListener(Listener *aListener) = 0;
    /**
     * Returns the product configuration this node was initialized with.
     */
    virtual IProductConfiguration *configuration() const = 0;
    /**
     * Returns the logs this node keeps.
     */
    virtual const Logs &logs() const = 0;
    /**
     * clears this node's logs
     */
    virtual void clearLogs() = 0;
    /**
     * Saves the state of this node into the given document. 
     * State means all information ( except input values or state )
     * that are needed to describe the state of the node at this point.
     */
    virtual void save(IDataDocument &aConfiguration) = 0;
    /**
     * Restores the state of this node based on the information in given
     * document.
     */
    virtual void load(IDataDocument &aConfiguration) = 0;
};

} // namespace us
