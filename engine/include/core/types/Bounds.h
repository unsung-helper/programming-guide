#pragma once

#include "Vec3.h"

namespace us {

class Bounds
{
public:
    Bounds();

    Bounds(Vec3 aMin, Vec3 aMax);

    void add(Vec3 aPos);

    bool isValid() const;

    Vec3 min() const;

    Vec3 max() const;

    Vec3 extent() const;

    bool contains(const Vec3 &aP) const;

    std::pair<double, double> interval(const Vec3 &aOrigin, const Vec3 &aDirection) const;

    bool operator==(const Bounds &aOther) const;

private:
    Vec3 _min;
    Vec3 _max;
};

} // namespace us
