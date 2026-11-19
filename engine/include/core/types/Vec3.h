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

#include "Eigen/Core"
#include "Eigen/Geometry"
#include <memory>

namespace us {

using Vec2 = Eigen::Vector2d;

using Vec3 = Eigen::Vector3d;

using Mat3 = Eigen::Matrix3d;

using Mat4 = Eigen::Matrix4d;

using Transformation = Eigen::Affine3d;

using Transformations = std::shared_ptr<std::vector<Transformation>>;
}
