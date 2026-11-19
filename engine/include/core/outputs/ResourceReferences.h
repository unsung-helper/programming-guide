/*
 * Copyright (c) 2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */
#pragma once

#include <cstdint>
#include <unordered_set>

namespace us {

/**
 * The geometry or material ids a listener of several mesh or polyline outputs
 * has handled (see IMeshProductOutput::Listener). Every output reports the
 * Added and Removed of an id, so the listener handles only the first of each.
 */
class ResourceReferences
{
public:
    /**
     * @return whether the id wasn't known until now
     */
    bool add(std::uint64_t aID) { return _ids.insert(aID).second; }

    /**
     * @return whether the id was known until now
     */
    bool remove(std::uint64_t aID) { return _ids.erase(aID) > 0; }

    bool contains(std::uint64_t aID) const { return _ids.contains(aID); }

private:
    std::unordered_set<std::uint64_t> _ids;
};

} // namespace us
