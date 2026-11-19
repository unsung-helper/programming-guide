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

#include "Bounds.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "URI.h"
#include <memory>

namespace us {

class Lighting
{
public:
    bool _cameraLight{true};

    Color _cameraLightColor{1, 1, 1};

    Color _ambientLightColor{0.05, 0.05, 0.05};

    std::vector<PointLight> _pointLights;

    std::vector<DirectionalLight> _directionalLights;

    Bounds _shadowBounds{};

    // Image based lighting from an equirectangular HDR image (.hdr or .exr), none when
    // invalid. The ambient light is ignored while there is one.
    URI _environmentMap;

    // scales the light of the environment map
    float _environmentIntensity{1.0f};

    // in degrees, around +Z. At 0 the center of the image lies in the +X direction and
    // its top row is +Z.
    float _environmentRotation{0.0f};
};

using LightingPtr = std::shared_ptr<Lighting>;

} // namespace ds
