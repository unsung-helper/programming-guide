/*
 * Copyright (c) 2024 Jucon BV
 * All rights reserved.
 *
 * This file is part of dsign. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */
#pragma once

#include "core/ANode.h"
#include "core/NodeInputT.h"
#include "core/NodeOutputT.h"
#include "core/types/Mesh.h"

namespace {
static const std::string RADIANS = "radians";
static const std::string DEGREES = "degrees";
} // namespace

namespace us {

/**
 * The Twist node twists a mesh around the Z-axis so that the 
 * total 'torque' between top and bottom of the object equals
 * the given angle. The angle can be provided in degrees as
 * well as radians, depending on the node's mode.
 * 
 * Twist is a subclass of ANode, which takes care of most of
 * INode's implementation, leaving implementers with 
 * execution and determining required dependencies. 
 * 
 * Twist also implements INodeInput::Listener to listen
 * for changes in its 'mode' unconnectable input's
 * fallback value. This value determines whether Twist
 * needs an angle input in degrees or in radians.
 */
class Twist : public ANode, public INodeInput::Listener
{
public:
    /**
     * The Twist node definition, defined as an inner class,
     * so that it has access to Twist's private constructor.
     * 
     * Please use AnodeDefinition to derive from when implementing
     * your own definitions. It takes care of registering node instances
     * of its definition for you.
     */
    class Definition : public ANodeDefinition
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
        INode *create(IProductConfiguration *aConfiguration,
                      const std::string &aID,
                      const ExtensionProviders &aExtensionProviders,
                      const NodePosition &aPosition) override;
    };

    virtual ~Twist();

    ///Returns the list of dependencies that need to be updated before this node
    ///can execute the given target and pass. Twist re-implements ANode's default
    ///implementation for demonstrational purposes.
    std::vector<INodeOutput *> requiredDependencies(Target aTarget, const Pass &aPass) override;
    ///Handles changes in _mode's fallback value
    void onFallbackValueChanged(INodeInput *aInput) override;

protected:
    ///Executes the node for given target and pass.
    void executeImpl(Target aTarget, const Pass &aPass) override;

private:
    Twist(Definition *aDefinition,
          IProductConfiguration *aProduct,
          const std::string &aID,
          const ExtensionProviders &aExtensionProviders,
          NodePosition aPosition);

    //the input mesh that this node twists
    NodeInputT<MeshPtr> _mesh;
    //the mode, either radians or degrees
    NodeInputT<std::string> _mode;
    //a dynamic input. Depending on the mode
    //either a degrees or a radians input
    //is used.
    std::unique_ptr<NodeInput> _angle;
    //the twisted output mesh
    NodeOutputT<MeshPtr> _result;
};

} // namespace us
