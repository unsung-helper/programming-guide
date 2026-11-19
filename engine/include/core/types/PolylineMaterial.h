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
#include <string>

namespace us {

class PolylineMaterial
{
public:
    PolylineMaterial();

    Color &color();

    Color color() const;

    float &lineWidth();

    float lineWidth() const;

    float &opacity();

    float opacity() const;

    bool &glow();

    bool glow() const;

    bool &outline();

    bool outline() const;

    Color &outlineColor();

    Color outlineColor() const;

    // in device-independent pixels
    float &outlineThickness();

    float outlineThickness() const;

    bool operator==(const PolylineMaterial &aOther) const;

    std::string toString() const;

    static PolylineMaterial fromString(const std::string &aString);

private:
    Color _color;

    float _lineWidth;

    float _opacity;

    bool _glow;

    bool _outline;

    Color _outlineColor;

    float _outlineThickness;
};

} // namespace us
