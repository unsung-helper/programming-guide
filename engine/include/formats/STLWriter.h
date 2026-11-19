#pragma once

#include "core/ITypeWriter.h"

namespace us {

class STLWriter : public us::ITypeWriter
{
public:
    STLWriter() = default;

    virtual ~STLWriter() = default;

    std::type_index type() const override;

    std::string format() const override;

    void write(const Any &aAsset, std::ostream &aOut) const override;
};

} // namespace us
