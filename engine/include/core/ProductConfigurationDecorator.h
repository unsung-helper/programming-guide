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

#include "IProductConfiguration.h"

namespace us {

class ProductConfigurationDecorator : public IProductConfiguration
{
public:
    ProductConfigurationDecorator(IProductConfiguration *aDelegate);

    virtual ~ProductConfigurationDecorator();

    void addParameter(IProductParameter *aParameter) override;

    void removeParameter(IProductParameter *aParameter) override;

    void addOutput(IProductOutput *aOutput) override;

    void removeOutput(IProductOutput *aOutput) override;

    void addEndpoint(INode *aNode, const std::unordered_set<Target> &aTargets) override;

    void removeEndpoint(INode *aNode) override;

    Any decode(const URI &aURI) override;

    void encode(const Any &aValue, const URI &aURI) override;

    std::type_index typeOf(const URI &aURI) override;

    std::vector<std::string> availableReaderFormats(const std::type_index &aType) const override;

    Any defaultValue(std::type_index aType) override;

    std::vector<std::string> availableWriterFormats(std::type_index aType) const override;

    std::pair<us::Any, bool> convert(const Any &aSource, std::type_index aTarget) override;

    void addListener(Listener *aListener) override;

    void removeListener(Listener *aListener) override;

    std::unordered_set<Pass> passes() const override;

    Logs::Level logLevel() const override;

    bool canceled() const override;

    Any decode(const std::string &aFormat, std::istream &aIn) override;

    void encode(const Any &aValue, const std::string &aFormat, std::ostream &aOut) override;

    void read(const URI &aURI, std::ostream &aStream) override;

    IDisplay *display() const override;

protected:
    IProductConfiguration *delegate() const;

private:
    IProductConfiguration *_delegate;
};

} // namespace us
