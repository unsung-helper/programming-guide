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

#include <string>

namespace us {

/**
 * Remembers the location of the app. In the browser, that is the directory the
 * wasm was loaded from, which only the main thread knows (see pre.js): call it
 * there, before any other thread asks for the location.
 */
void initAppLocation();

/**
 * The location of the app, ending in a '/', or empty when unknown. Callable
 * from any thread once initAppLocation() has run.
 */
std::string getAppLocation();

} // namespace us
