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

#include <set>
#include <string>
#include <vector>

namespace us {

/**
 * Unsung helper runs the same graph multiple times, on different
 * input data. Every such run is defined by its Pass.
 * 
 * Each node in the graph should be aware that it can be run 
 * multiple times. It needs to maintain state and values per Pass.
 * 
 * However in some cases by design a node returns the same value regardless
 * of which pass is run ( e.g. a constant asset ). In that case a single
 * run is sufficient. To communicate this nodes can group Passes in PassesGroups:
 * when Passes are in the same PassesGroup, it means that nodes will return
 * the same value for Passes in the same PassesGroup. With this information
 * Unsung Helper can optimize graph traversal.
 * 
 * For any node in the graph this partitioning of Passes into groups depends
 * on its implementation as well as the partitioning of all its inputs. The partition()
 * utility method here takes care of that.
 */
using Pass = std::string;
using PassesGroup = std::set<Pass>;
using PassesGroups = std::set<PassesGroup>;

/**
 * Takes a list of PassesGroups as input, assuming that each PassesGroups
 * contains the same Passes. It returns a PassesGroups so that any two Passes
 * end up in the same PassesGroup if and only if they are in the same PassesGroup
 * in every PassesGroup in the input list. A PassesGroup with only a single Pass
 * is omitted from the result.
 */
PassesGroups partition(const std::vector<PassesGroups> &aGroups);

} // namespace us
