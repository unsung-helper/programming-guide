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
#include "core/NodeInput.h"
#include "core/NodeInputT.h"
#include "core/NodeOutput.h"
#include "remote/RemoteCall.h"

namespace us {

class RemoteNodeDecorator : public ANode, public INode::Listener, public INodeInput::Listener
{
public:
    using CallerProvider = std::function<std::unique_ptr<RemoteCall>(IProductConfiguration *)>;

    class Definition : public ANodeDefinition
    {
    public:
        Definition(std::unique_ptr<INodeDefinition> &&aDefinition, CallerProvider aCallerProvider);

        std::string type() const override;

        std::string description() const override;

        INode *create(IProductConfiguration *aConfiguration,
                      const std::string &aID,
                      const ExtensionProviders &aExtensionProviders,
                      const NodePosition &aPosition) override;

        INodeDefinition *definition() const;

        const std::unordered_map<std::string, std::string> &headers() const;

    private:
        std::unique_ptr<INodeDefinition> _definition;
        CallerProvider _callerProvider;
    };

    virtual ~RemoteNodeDecorator();

    void onInputsChanged(INode *aNode) override;
    void onOutputsChanged(INode *aNode) override;

    void onFallbackValueChanged(INodeInput *aInput) override;
    void onOptionsChanged(INodeInput *aInput) override;

protected:
    void executeImpl(Target aTarget, const Pass &aPass) override;

private:
    RemoteNodeDecorator(Definition *aDefinition,
                        IProductConfiguration *aConfiguration,
                        const std::string &aID,
                        const ExtensionProviders &aExtensionProviders,
                        const NodePosition &aPosition,
                        CallerProvider aCallerProvider);

    void updateInputs();

    void updateOutputs();

    IProductConfiguration *_configuration;

    std::unique_ptr<INode> _delegate;

    std::unordered_map<INodeInput *, std::unique_ptr<NodeInput> > _inputs;

    std::unordered_map<INodeOutput *, std::unique_ptr<NodeOutput> > _outputs;

    CallerProvider _callerProvider;

    us::NodeInputT<bool> _remote;
};

} // namespace us
