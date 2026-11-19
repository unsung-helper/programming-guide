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
#include <array>
#include <cmath>

namespace us {

class Color
{
public:
    Color();

    Color(double aR, double aG, double aB);

    double r() const;
    double g() const;
    double b() const;

    double &r();
    double &g();
    double &b();

    Color &operator+=(const Color &aOther);

    Color operator+(const Color &aOther) const;

    Color &operator-=(const Color &aOther);

    Color operator-(const Color &aOther) const;

    Color &operator*=(double aF);

    Color operator*(double aF) const;

    static bool equals(const Color &aF, const Color &aS);

private:
    std::array<double, 3> _c;
};

Color operator*(double aF, const Color &aColor);

Color lerp(const Color &aFirst, const Color &aSecond, double aF);

} // namespace us
