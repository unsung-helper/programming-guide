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

#include "core/ANode.h"
#include "core/NodeInputT.h"
#include "core/NodeOutputT.h"
#include "Degrees.h"
#include <memory>

/**
 * AngleParameter defines a node that registers a number
 * parameter to the product that and outputs the value as
 * an angle in Degrees.
 */
class AngleParameter : public us::ANode
{
public:
    /**
     * The AngleParameter node definition, defined as an inner class,
     * so that it has access to Twist's private constructor.
     * 
     * Please use AnodeDefinition to derive from when implementing
     * your own definitions. It takes care of registering node instances
     * of its definition for you.
     */
    class Definition : public us::ANodeDefinition
    {
    public:
        Definition();

        ///The type of this node. This name should be unique among all registered
        ///node definitions. If a duplicate is registered, the definition registered
        ///last is kept.
        std::string type() const override;
        ///The description of the node definition as seen in its info dialog and
        ///Node details panel.
        std::string description() const override;
        ///Creates a new node based on this definition.
        ///@param aConfiguration the product configuration handle for the new node
        ///Note that not all nodes get assigned the same configuration. For instance
        ///nodes in a template receive a different configuration than those in the
        ///Main graph.
        ///@param aID a unique ID assigned to the node by the engine.
        ///@param aExtensionProviders a list of objects that create extensions
        ///that modify node behavior. For instance this is used to implement
        ///a caching strategy while executing the graph. Unless you have deep
        ///technical understanding of the engine it is best to leave extensions
        ///for now.
        ///@param aPosition the position of the new node in the design canvas.
        INode *create(us::IProductConfiguration *aConfiguration,
                      const std::string &aID,
                      const us::ExtensionProviders &aExtensionProviders,
                      const us::NodePosition &aPosition) override;
    };

    virtual ~AngleParameter();

    ///Returns the list of dependencies that need to be updated before this node
    ///can execute the given target and pass.
    std::vector<us::INodeOutput *> requiredDependencies(us::Target aTarget,
                                                        const us::Pass &aPass) override;
    ///Saves all values that this node needs to restore the current
    ///state of the configurator.
    void save(us::IDataDocument &aConfiguration) override;
    ///Restores the state of this node based on the given configuration
    void load(us::IDataDocument &aConfiguration) override;

protected:
    ///Executes this node for given target and pass
    void executeImpl(us::Target aTarget, const us::Pass &aPass) override;
    ///ANode callback when a pass was added. This node
    ///uses it to update its state
    void onBeginAddPass(const us::Pass &aPass) override;
    ///ANode callback when a pass was removed. This node
    ///uses it to update its state
    void onBeginRemovePass(const us::Pass &aPass) override;
    ///Passes information on which passes yield exactly the
    ///same result for this node. A single PassesGroup groups
    ///passes that return identical results. When a pass does
    ///not occur in the result, that means the result of that
    ///pass is unique.
    us::PassesGroups partitionGroups() const override;

private:
    AngleParameter(Definition *aDefinition,
                   us::IProductConfiguration *aProductConfiguration,
                   const std::string &aID,
                   const us::ExtensionProviders &aExtensionProviders,
                   const us::NodePosition &aPosition);

    //For every pass the AngleParameter registers a parameter
    //implements INumberParameter
    class AngleRegisteredParameter;
    std::unordered_map<us::Pass, std::unique_ptr<AngleRegisteredParameter>> _d;
    //the output, in Degrees
    us::NodeOutputT<Degrees> _output;
    //Property for controlling the visibility of the parameter
    us::NodeInputT<bool> _visible;
    //The default value of this parameter. If the default
    //value changes, the value of the parameter changes as well.
    us::NodeInputT<float> _defaultValue;
};

