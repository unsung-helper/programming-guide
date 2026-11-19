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
#include "Degrees.h"

Degrees::Degrees(double aValue)
    : _value(aValue)
{}

Degrees::operator double() const
{
    return _value;
}
