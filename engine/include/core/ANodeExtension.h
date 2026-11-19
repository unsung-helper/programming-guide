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
#include "core/Pass.h"
#include <memory>
#include <unordered_set>
#include <vector>

namespace us {

class INode;
class INodeInputInternal;
class INodeOutputInternal;

/**
 * This class can be used to extend INode implementations. It acquires
 * handles to the in- and outputs of an INode which enable it to
 * manipulate some of the inner workings of the INode. As such it should
 * never be shared. As such it should never be copied.
 */
class ANodeExtension
{
public:
    ANodeExtension(INode *aNode);

    virtual ~ANodeExtension();

    ANodeExtension(const ANodeExtension & aOther) = delete;
    ANodeExtension(ANodeExtension && aOther) = default;
    ANodeExtension & operator = (const ANodeExtension & aOther) = delete;
    ANodeExtension & operator = (ANodeExtension && aOther) = default;

    /**
     * Executed before the node is executed
     */
    void beforeExecute(Target aTarget, const Pass &aPass);
    /**
     * Executed after the node is executed
     */
    void afterExecute(Target aTarget, const Pass &aPass);
    /**
     * Registers the given input to this extension.
     * This extension does not take ownership of the
     * given input. It expects that it is unregistered
     * before the end of the input's lifetime.
     */
    void registerInput(INodeInputInternal * aInput);
    /**
     * Registers the given output to this extension.
     * This extension does not take ownership of the
     * given output. It expects that it is unregistered
     * before the end of the output's lifetime.
     */
    void registerOutput(INodeOutputInternal * aOutput);
    /**
     * Unregisters the given input
     */
    void unregisterInput(INodeInputInternal * aInput);
    /**
     * Unregisters the given output
     */
    void unregisterOutput(INodeOutputInternal * aOutput);

protected:
    INode *node() const;

    const std::unordered_set<INodeInputInternal *> & inputs();

    const std::unordered_set<INodeOutputInternal *> & outputs();

    virtual void onBeforeExecute(Target aTarget, const Pass &aPass);

    virtual void onAfterExecute(Target aTarget, const Pass &aPass);

    virtual void onInputRegistered(INodeInputInternal * aInput);

    virtual void onOutputRegistered(INodeOutputInternal * aOutput);

    virtual void onInputUnregistered(INodeInputInternal * aInput);

    virtual void onOutputUnregistered(INodeOutputInternal * aOutput);


private:
    INode *_node;

    std::unordered_set<INodeInputInternal *> _inputs;

    std::unordered_set<INodeOutputInternal *> _outputs;
};

using NodeExtensionPtr = std::unique_ptr<ANodeExtension>;

using NodeExtensionList = std::vector<NodeExtensionPtr>;

} // namespace us
