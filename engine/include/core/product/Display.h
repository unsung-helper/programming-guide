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

#include "core/IDisplay.h"

namespace us {

class Display : public IDisplay
{
public:
    Display();

    Camera camera() const override;

    Dimensions dimensions() const override;

    void addListener(Listener *aListener) override;

    void removeListener(Listener *aListener) override;

    Outcome passMouseEvent(MouseGesture aGesture,
                           MouseButton aButton,
                           const Position &aPosition,
                           Modifiers aModifiers);

    Outcome passWheelEvent(float aDelta, Modifiers aModifiers);

    void setCamera(const Camera &aCamera);

    void setDimensions(const Dimensions &aDimensions);

private:
    std::vector<Listener *> _listeners;

    Dimensions _dimensions;

    Camera _camera;
};

} // namespace us
