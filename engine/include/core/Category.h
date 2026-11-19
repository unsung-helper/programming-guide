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

namespace us {

class Category
{
public:
    Category() = default;
    ~Category() = default;
    Category(const Category &) = default;
    Category(Category &&) = default;
    Category &operator=(const Category &) = default;
    Category &operator=(Category &&) = default;

    size_t depth() const;

    std::string tag(size_t aDepth) const;

    Category operator<<(const std::string &aAdditionalTag) const;

    bool operator<(const Category &aOther) const;

    bool operator==(const Category &aOther) const;

private:
    std::vector<std::string> _tags;
};

} // namespace us
