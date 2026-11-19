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

/**
 * A class describing an angle in degrees.
 */
class Degrees
{
public:
    Degrees(double aValue = 0.0);

    operator double() const;

private:
    double _value;
};
