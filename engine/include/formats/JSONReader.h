#pragma once

#include "core/ITypeReader.h"

namespace us {

class JSONReader : public ITypeReader
{
public:
    JSONReader() = default;

    virtual ~JSONReader() = default;

    std::type_index type() const override;

    std::vector<std::string> formats() const override;

    Any read(std::istream &aIn) const override;
};

} // namespace us
