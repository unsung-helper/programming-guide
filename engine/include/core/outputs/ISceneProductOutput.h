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

#include "IProductOutput.h"
#include "core/types/Camera.h"
#include "core/types/Lighting.h"
#include "core/types/Vec3.h"
#include <memory>

namespace us {

class ISceneProductOutput : public us::IProductOutput
{
public:

    class Update
    {
    public:
        enum class BackgroundMode { None, Color, Environment };

        // How lit surfaces and the environment background are mapped to displayable
        // colors, like three.js' tone mappings of the same names
        enum class ToneMapping { None, Neutral, ACES, AgX };

        CameraPtr _camera;
        LightingPtr _lighting;
        bool _showFrameRate = false;
        // None: the preview is transparent, whatever is behind it shows
        BackgroundMode _backgroundMode = BackgroundMode::None;
        Color _backgroundColor;
        // Environment: the lighting's environment map (None without one), blurred as if
        // reflected by a surface of this roughness (0..1) and scaled by the intensity
        float _backgroundBlur = 0.0f;
        float _backgroundIntensity = 1.0f;

        ToneMapping _toneMapping = ToneMapping::Neutral;
        // multiplies the light of lit surfaces and the environment background, before
        // the tone mapping (also without one)
        float _exposure = 1.0f;
        std::string _displayName;
        std::string _description;
        std::string _externalID;

        // whether objects cast a soft contact shadow onto a ground plane
        bool _contactShadowEnabled = false;
        // places the contact shadow plane, the XY plane by default. Only its
        // rotation and translation are used.
        Transformation _contactShadowOrientation = Transformation::Identity();
    };

    /**
     * Base class for an ISceneProductOutput Listener
     */
    class Listener
    {
    public:
        virtual void onUpdate(ISceneProductOutput *aOutput, const Update &aUpdate);
    };

    virtual ~ISceneProductOutput();

    /**
     * Adds a Listener
     * @note This ISceneProductOutput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this ISceneProductOutput's lifetime.
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the given Listener
     */
    virtual void removeListener(Listener *aListener) = 0;
};

} // namespace us
