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

#include "core/IDataStore.h"

namespace us {

class DataUrlDataStore : public IDataStore
{
public:
    DataUrlDataStore();

    virtual ~DataUrlDataStore();

    bool readable() const override;

    bool writable() const override;

    bool read(const URI &aUri, std::ostream &aContents) override;

    bool write(const URI &aUri, std::istream &aContents) override;

    std::unordered_set<std::string> protocols() const override;
};

} // namespace us
