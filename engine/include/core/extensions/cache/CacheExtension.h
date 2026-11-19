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

#include "core/ANodeExtension.h"
#include <chrono>
#include "core/INodeInput.h"
#include "core/INodeOutput.h"


namespace us {

/**
 * Caching strategy for nodes. Whenever all connections of an output have accepted
 * the most recent value, the value is released from memory, unless it takes longer
 * than 1000ms to recompute the value.
 */
class CacheExtension : public us::ANodeExtension, public INodeInput::Listener , public INodeOutput::Listener
{
public:
    /**
     * Creates new CacheExtension
     */
    CacheExtension(INode *aNode);

    /**
     * @copydoc INodeInput::Listener::onStateChanged
     */
    void onStateChanged(INodeInput *aInput,
                        INodeInput::State aState,
                        const Pass &aPass) override;

    /**
     * @copydoc INodeOutput::Listener::onConnectionAdded
     */
    void onConnectionAdded(INodeOutput *aOutput, INodeInput *aConnection) override;
    /**
     * @copydoc INodeOutput::Listener::onConnectionRemoved
     */
    void onConnectionRemoved(INodeOutput *aOutput, INodeInput *aConnection) override;

protected:
    /**
     * @copydoc ANodeExtension::onBeforeExecute
     */
    void onBeforeExecute(Target aTarget, const Pass &aPass) override;
    /**
     * @copydoc ANodeExtension::onAfterExecute
     */
    void onAfterExecute(Target aTarget, const Pass &aPass) override;
    /**
     * @copydoc ANodeExtension::onOutputRegistered
     */
    void onOutputRegistered(INodeOutputInternal *aOutput) override;
    /**
     * @copydoc ANodeExtension::onOutputUnregistered
     */
    void onOutputUnregistered(INodeOutputInternal *aOutput) override;

private:

    /*
     * checks the state of the connections of the given output.
     * If the given output has an available value, and all connections
     * have already accepted this value, this method releases
     * the output's value, unless it takes longer than 1000ms
     * to re-execute the output's node.
     */
    void checkCaching(INodeOutputInternal *aOutput, const Pass &aPass);

    std::unordered_map<INodeInput *, INodeOutputInternal *> _connectionMap;

    std::chrono::steady_clock::time_point _start;

    uint64_t _duration;

};

} // namespace us
