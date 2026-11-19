#pragma once

#include "core/types/Font.h"
#include "core/types/Mesh.h"
#include "core/types/Polyline.h"

namespace us {

class GeometryFromTextUtil
{
public:
    GeometryFromTextUtil();

    us::PolylinePtr textToPolyline(FontPtr aFont, double aSize, const std::string &aText);

    us::MeshPtr textToMesh(FontPtr aFont, double aSize, const std::string &aText);
};

} // namespace us
