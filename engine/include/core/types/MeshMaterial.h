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

#include "core/types/Color.h"
#include "core/types/URI.h"

namespace us {

class MeshMaterial
{
public:
    enum class ShadingModel { Opaque, Wireframe };

    MeshMaterial();

    Color &color();

    Color color() const;

    float &roughness();

    float roughness() const;

    float &metallic();

    float metallic() const;

    float &opacity();

    float opacity() const;

    bool doubleSided() const;

    bool &doubleSided();

    bool castsShadow() const;

    bool &castsShadow();

    bool glow() const;

    bool &glow();

    bool outline() const;

    bool &outline();

    Color outlineColor() const;

    Color &outlineColor();

    // in device-independent pixels
    float outlineThickness() const;

    float &outlineThickness();

    ShadingModel &model();

    ShadingModel model() const;

    const URI &texture() const;

    URI &texture();

    bool operator==(const MeshMaterial &aOther) const;

    std::string toString() const;

    static MeshMaterial fromString(const std::string &aString);

private:
    Color _color;

    float _roughness;

    float _metallic;

    float _opacity;

    bool _doubleSided;

    ShadingModel _model;

    URI _texture;

    bool _castsShadow;

    bool _glow;

    bool _outline;

    Color _outlineColor;

    float _outlineThickness;
};

} // namespace us
