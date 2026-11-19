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
#include "core/Any.h"
#include "core/types/URI.h"
#include <unordered_set>

namespace us {


class INode;
class IProductParameter;
class IProductOutput;
class EnumerationType;
class IDisplay;

/**
 * Interface exposing product-wide functionality to instances of INode
 */
class IProductConfiguration
{
public:
    class Listener
    {
    public:
        virtual void onBeginAddPass(const Pass &aPass);
        virtual void onEndAddPass(const Pass &aPass);
        virtual void onBeginRemovePass(const Pass &aPass);
        virtual void onEndRemovePass(const Pass &aPass);
    };

    /**
     * Registers a parameter to the current product.
     * @note IProductConfiguration does not take ownership of the
     * given parameter. It actively uses the provided parameter
     * to update its values. Make sure to remove the parameter
     * again before its lifetime is expired.
     */
    virtual void addParameter(IProductParameter *aParameter) = 0;
    /**
     * Unregisters the given parameter from the current product.
     */
    virtual void removeParameter(IProductParameter * aParameter) = 0;
    /**
     * Registers the given output to the current product.
     * @note IProductConfiguration does not take ownership of the
     * given output. Make sure to remove the output
     * again before its lifetime is expired.
     */
    virtual void addOutput(IProductOutput * aOutput) = 0;
    /**
     * Unregisters the given output from the current product
     */
    virtual void removeOutput(IProductOutput * aOutput) = 0;
    /**
     * Registers the given node as an endpoint. When evaluating
     * a product the traversal algorithm traces back and
     * executes nodes from every endpoint on.
     *
     * @note IProductConfiguration does not take ownership of the
     * given endpoint. Make sure to remove the endpoint
     * again before its lifetime is expired.
     */
    virtual void addEndpoint(INode *aNode, const std::unordered_set<Target> &aTargets) = 0;
    /**
     * Unregisters the given node as an endpoint.
     */
    virtual void removeEndpoint(INode * aNode) = 0;

    virtual void read(const URI &aURI, std::ostream &aStream) = 0;

    /**
     * Decodes the given URI
     */
    virtual Any decode(const URI & aURI) = 0;

    virtual Any decode(const std::string &aFormat, std::istream &aIn) = 0;

    virtual void encode(const Any &aValue, const URI &aURI) = 0;

    virtual void encode(const Any &aValue, const std::string &aFormat, std::ostream &aOut) = 0;

    /**
     * Returns the type information associated with the given URI.
     */
    virtual std::type_index typeOf(const URI &aURI) = 0;

    virtual Any defaultValue(std::type_index aType) = 0;

    virtual std::pair<Any, bool> convert(const Any &aSource, std::type_index aTarget) = 0;

    /**
     * Returns which URI extensions can be decoded for a given type
     */
    virtual std::vector<std::string> availableReaderFormats(const std::type_index &aType) const = 0;

    virtual std::vector<std::string> availableWriterFormats(std::type_index aType) const = 0;

    virtual void addListener(Listener *aListener) = 0;

    virtual void removeListener(Listener *aListener) = 0;

    virtual std::unordered_set<Pass> passes() const = 0;

    virtual Logs::Level logLevel() const = 0;

    virtual bool canceled() const = 0;

    virtual IDisplay *display() const = 0;
};

} // namespace us
