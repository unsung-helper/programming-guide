#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>

namespace us {

class UUIDGen
{
public:
    UUIDGen();

    std::string generate();

private:
    std::mt19937_64 rng;
    std::array<std::uint32_t, 8> seed_data;
};

} // namespace us
