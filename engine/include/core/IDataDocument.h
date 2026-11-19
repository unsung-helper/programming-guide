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

#include <string>
#include <vector>
#include <unordered_set>

namespace us {

class IDataDocument
{
public:
    virtual ~IDataDocument();

    virtual std::vector<std::string> stack() const = 0;

    virtual bool push(const std::string & aKey) = 0;

    virtual bool pop() = 0;

    virtual void finish() = 0;

    virtual bool create(const std::string & aKey) = 0;

    virtual bool insert(const std::string & aKey, const std::string & aValue) = 0;

    virtual std::unordered_set<std::string> children() const = 0;

    virtual std::unordered_set<std::string> values() const = 0;

    virtual std::string value(const std::string & aKey) const = 0;

    virtual bool hasKey(const std::string &aKey) const = 0;

    virtual void setData(const std::string & aData) = 0;

    virtual std::string data() const = 0;


};

} // namespace us
