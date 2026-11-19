#pragma once

#include "core/outputs/IPolylineProductOutput.h"
#include "core/types/Polyline.h"

namespace us {

std::shared_ptr<IPolylineProductOutput::Geometry> createPolylineGeometry(const PolylinePtr aPolyline);

} // namespace us
