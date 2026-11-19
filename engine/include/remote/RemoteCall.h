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

#include "HeaderProvider.h"
#include "core/Any.h"
#include "core/INodeInput.h"
#include "core/INodeOutput.h"
#include <unordered_map>

namespace us {

class IProductConfiguration;
class INode;

class RemoteCall
{
public:
    using Result = std::unordered_map<std::string, Any>;

    RemoteCall(IProductConfiguration *aConfiguration,
               const std::string &aLocation,
               HeaderProvider aHeaderProvider);

    std::tuple<bool, std::string, Result> execute(
        const std::string &aID,
        const std::string &aType,
        const std::unordered_map<std::string, Any> &aInputs,
        const std::unordered_map<std::string, std::type_index> &aExpected);

protected:
    std::unordered_map<std::string, std::string> headers(
        const std::unordered_map<std::string, std::string> &aAdditional
        = std::unordered_map<std::string, std::string>()) const;

    std::string location() const;

    virtual bool call(const std::string &aBody, std::ostream &aResponse);

private:
    IProductConfiguration *_configuration;
    HeaderProvider _headerProvider;
    std::string _location;
};

} // namespace us
