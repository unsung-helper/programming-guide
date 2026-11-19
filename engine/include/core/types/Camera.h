#pragma once

#include "Vec3.h"
#include <memory>

namespace us {

class Camera
{
public:
    Camera();
    Vec3 _position;
    Vec3 _up;
    Vec3 _target;

    double _fov;
    double _near;
    double _far;

    bool _lock;
};

using CameraPtr = std::shared_ptr<Camera>;

} // namespace us
