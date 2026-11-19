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

#include <functional>
#include <map>
#include <string>
#include <typeindex>
#include <unordered_set>

#include "Any.h"
#include "util/OrderedSet.h"

namespace us {

class TypeManager
{
public:
    using Types = std::pair<std::type_index, std::type_index>;
    using Conversion = std::function<Any(const Any &)>;

    class Listener
    {
    public:
        virtual void onTypeRegistered(std::type_index aType);
        virtual void onConversionRegistered(std::type_index aSource, std::type_index aTarget);
    };

    TypeManager() = default;

    virtual ~TypeManager() = default;

    void registerType(std::type_index aTypeInfo, const std::string &aName, const Any &aDefaultValue);

    bool hasType(std::type_index aTypeInfo) const;

    bool hasName(const std::string &aName) const;

    std::string name(std::type_index aTypeInfo) const;

    std::type_index type(const std::string &aName) const;

    Any defaultValue(std::type_index aType) const;

    std::unordered_set<std::string> typeNames() const;

    void registerConversion(std::type_index aSource,
                            std::type_index aTarget,
                            Conversion aConversion);

    bool hasConversion(std::type_index aSource, std::type_index aTarget) const;

    Conversion conversion(std::type_index aSource, std::type_index aTarget) const;

    std::vector<Types> availableConversions() const;

    void addListener(Listener *aListener);

    void removeListener(Listener *aListener);

private:

    std::unordered_map<std::type_index, std::string> _registeredTypes;

    std::unordered_map<std::string, std::type_index> _registeredNames;

    std::unordered_map<std::type_index, Any> _defaultValues;

    std::map<Types, Conversion> _conversions;

    OrderedSet<Listener *> _listeners;
};

} // namespace us


