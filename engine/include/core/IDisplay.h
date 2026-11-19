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

#include "core/types/Camera.h"

namespace us {

class IDisplay
{
public:
    using Modifier = int;
    using Modifiers = int;

    static constexpr Modifier NO_MODIFIER = 0;
    static constexpr Modifier CTRL_MODIFIER = 1 << 0;
    static constexpr Modifier ALT_MODIFIER = 1 << 1;
    static constexpr Modifier SHIFT_MODIFIER = 1 << 2;

    enum MouseButton { None = 0, Left = 1, Middle = 2, Right = 3 };
    enum MouseGesture { Press = 0, Move = 1, Release = 2 };

    using Dimensions = std::pair<int, int>;
    using Position = std::pair<int, int>;

    struct Outcome
    {
        bool _requiresExecution;
        bool _handled;
        Outcome(bool aRequiresExecution, bool aHandled);

        Outcome &operator|=(const Outcome &aOutcome);
    };

    class Listener
    {
    public:
        virtual ~Listener();

        virtual int priority() const;

        virtual Outcome onMouseEvent(MouseGesture aGesture,
                                     MouseButton aButton,
                                     const Position &aPosition,
                                     Modifiers aModifiers,
                                     Outcome aOutcome);
        virtual Outcome onWheelEvent(float aDelta, Modifiers aModifiers, Outcome aOutcome);

        virtual void onDimensionsChanged();

        virtual void onCameraChanged();
    };

    virtual ~IDisplay();

    virtual Camera camera() const = 0;

    virtual Dimensions dimensions() const = 0;

    virtual void addListener(Listener *aListener) = 0;

    virtual void removeListener(Listener *aListener) = 0;
};

} // namespace us
