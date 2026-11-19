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

#include "Any.h"
#include "INode.h"
#include "INodeConnector.h"

namespace us {

class INodeInput;

/**
 * Interface for INode outputs. An INodeOutput can connect to multiple
 * INodeInputs. Additionally it holds an Any value of the output's type
 * storing a result of the node's calculation.
 * Additionally it maintains a state, showing whether the output's
 * INode is invalid, up-to-date or released from memory.
 *
 * State and value are maintained per Pass. INodeOutput also 
 * communicates how its passes are partitioned into PassesGroups.
 */
class INodeOutput : public INodeConnector
{
public:
    virtual ~INodeOutput();

    ///Possible states of an INodeOutput
    enum class State {
        Invalid,   /// The value is not up-to-date. The node needs to re-execute.
        Available, /// The value is up-to-date.
        Released   /// The value was released from memory.
    };

    /**
     * Base class for observers of INodeOutput
     */
    class Listener {
    public:
        virtual void onStateChanged(INodeOutput *aOutput, State aState, const Pass &aPass);
        virtual void onConnectionAdded(INodeOutput * aOutput, INodeInput * aConnection);
        virtual void onConnectionRemoved(INodeOutput * aOutput, INodeInput * aConnection);
        virtual void onGroupsChanged(INodeOutput *aOutput);
    };

    /**
     * Returns the state of this INodeOutput
     */
    virtual State state(const Pass &aPass) const = 0;
    /**
     * Registers the given listener.
     * @note This INodeOutput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this INodeOutput's lifetime.
     */
    virtual void addListener(Listener * aListener) = 0;
    /**
     * Unregisters the given listener
     */
    virtual void removeListener(Listener * aListener) = 0;
    /**
     * Connects this output to the given input, if
     * not already connected.
     * This method is only successful when the types of
     * in- and output are the same. Otherwise its behavior
     * is undefined.
     *
     * @note before deleting an INodeOutput it should be
     * disconnected properly from all connections.
     * Failure to do so might result in undefined behavior.
     */
    virtual void connect(INodeInput * aInput) = 0;
    /**
     * Disconnects the given input from this output
     */
    virtual void disconnect(INodeInput *aInput) = 0;
    virtual void disconnect() = 0;
    /**
     * Returns a list of all connections
     */
    virtual std::vector<INodeInput *> connections() const = 0;
    /**
     * Returns whether this output is connected with given input, or not.
     */
    virtual bool hasConnectionWith(INodeInput * aInput) const = 0;
    /**
     * Returns the current value of this output.
     */
    virtual Any value(const Pass &aPass) const = 0;
    /**
     * Whether this output is constant or not
     */
    virtual bool constant() const = 0;
    /**
     * The constant value, if set
     */
    virtual Any constantValue() const = 0;
    /**
     * Returns the PassesGroups partitioning of this output.
     */
    virtual PassesGroups groups() const = 0;
};

} // namespace us
