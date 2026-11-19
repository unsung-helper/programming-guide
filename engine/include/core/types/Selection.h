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
#include <unordered_set>
#include <vector>

namespace us {

class Selection
{
public:
    enum class Operator { Equals, Not, And, Or, True, False };

    static Selection EQ(const std::string &aIdentifier);

    static Selection NOT(Selection &aSelection);

    static Selection AND(const std::vector<Selection> &aSelection);

    static Selection OR(const std::vector<Selection> &aSelection);

    static Selection ALL();

    static Selection NONE();

    Selection();

    virtual ~Selection();

    Selection(const Selection &aOther);

    Selection(Selection &&aOther);

    Selection &operator=(const Selection &aOther);

    Selection &operator=(Selection &&aOther);

    bool operator==(const Selection &aOther) const;

    bool operator!=(const Selection &aOther) const;

    bool matches(const std::unordered_set<std::string> &aIdentifiers) const;

    const std::string &identifier() const;

    std::string toString() const;

    static Selection fromString(const std::string &aString);

private:

    Operator _op;
    std::string _identifier;
    std::vector<Selection> _children;
};

} // namespace us
