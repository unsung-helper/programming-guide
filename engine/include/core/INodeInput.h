#pragma once

#include "Any.h"
#include "INodeConnector.h"
#include "Pass.h"
#include <unordered_set>
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

namespace us {

class INodeOutput;

/**
 * Interface for INode inputs. An INodeInput can connect to a single
 * INodeOutput. It either holds such a connection or an Any value
 * of the input's type.
 * Additionally it maintains a state, showing whether the input's
 * INode has accepted the input's value yet, or not.
 * 
 * State and value are maintained per Pass. INodeInput also 
 * communicates how its passes are partitioned into PassesGroups.
 */
class INodeInput : public INodeConnector
{
public:

    ///The possible states of an INodeInput
    enum class State {
        Invalid, /// The node has not used the latest value of the input yet
        Accepted /// The node has used the latest value.
    };

    /**
     * Base class for observers of INodeInput
     */
    class Listener {
    public:
        virtual void onStateChanged(INodeInput *aInput, State aState, const Pass &aPass);
        virtual void onConnectionChanged(INodeInput *aInput);
        virtual void onFallbackValueChanged(INodeInput *aInput);
        virtual void onOptionsChanged(INodeInput *aInput);
        virtual void onError(INodeInput *aInput, const std::string &aErrorMessage);
        virtual void onGroupsChanged(INodeInput *aOutput);
    };

    virtual ~INodeInput();

    /**
     * Returns the state of this INodeInput
     */
    virtual State state(const Pass &aPass) const = 0;
    /**
     * Registers the given listener.
     * @note This INodeInput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this INodeInput's lifetime.
     */
    virtual void addListener(Listener * aListener) = 0;
    /**
     * Unregisters the given listener
     */
    virtual void removeListener(Listener * aListener) = 0;
    /**
     * Connects this input to the given output.
     * If this input was already connected to another
     * output, the input is disconnected properly first.
     * Creating a new connection invalidates this input,
     * and clears the value it holds.
     * This method is only successful when the types of
     * in- and output are the same. Otherwise its behavior
     * is undefined.
     *
     * @note before deleting an INodeInput it should be
     * disconnected properly. Failure to do so might
     * result in undefined behavior.
     */
    virtual void connect(INodeOutput * aOutput) = 0;
    /**
     * Disconnects this input.
     * This invalidates this input.
     */
    virtual void disconnect() = 0;
    /**
     * Returns the output this input is connected to,
     * or nullptr if it is not connected.
     */
    virtual INodeOutput * connection() const = 0;
    /**
     * If there is a connection, this method returns the
     * value of the connected output. If not it returns
     * the value held by this input.
     */
    virtual Any value(const Pass &aPass) const = 0;
    /**
     * Sets the value of this input. This method
     * only runs successfully when this input is not
     * connected and when the given value holds the
     * same type as what this input expects. Otherwise
     * the behavior of this method is undefined.
     * This method invalidates the input.
     */
    virtual void setFallbackValue(const Any &aValue) = 0;
    /**
     * Returns the value of this input, regardless
     * of whether it is connected or not.
     */
    virtual Any fallbackValue() const = 0;
    /**
     * Returns whether this input can be connected or not
     */
    virtual bool canConnect() const = 0;
    /**
     * Returns the values this input can assume. If empty this input can assume any value.
     */
    virtual const std::unordered_set<Any> &options() const = 0;
    /**
     * Returns the PassesGroups partitioning of this input.
     */
    virtual PassesGroups groups() const = 0;
};

} // namespace us
