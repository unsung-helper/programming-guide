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

#include "core/Pass.h"
#include <string>
#include <tuple>
#include <vector>
namespace us {

class Logs
{
public:
    enum Level { Error = 0, Warning = 1, Info = 2, Debug = 3, NbLevels = 4 };

    using Entry = std::tuple<Level, std::string, std::string>;

    void clear();

    int nbEntries() const;

    const Entry &entry(int aIdx) const;

    void add(Level aLevel, const Pass &aPass, const std::string &aMessage);

private:
    std::vector<Entry> _entries;
};

} // namespace us
