
#pragma once

#include <cstdint>
#include <array>
#include <vector>


namespace chu
{
    size_t hashArr(const std::array<uint8_t, 16>& arr);
    size_t hashArr(const std::array<uint8_t, 13>& arr);

    size_t hashVec(const std::vector<uint8_t>& vec);

}
