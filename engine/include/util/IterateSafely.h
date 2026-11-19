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

#include "util/OrderedSet.h"
#include <functional>

namespace us {

template<typename T>
void iterateSafely(const OrderedSet<T *> &aListeners, std::function<void(T *)> aCallback)
{
    auto listeners = aListeners;
    for (auto it = listeners.begin(); it != listeners.end(); ++it) {
        T *listener = *it;
        if (aListeners.contains(listener)) {
            aCallback(listener);
        }
    }
}

} // namespace us
