
#include <mxf_exploring/Hasher.hpp>


size_t chu::hashArr(const std::array<uint8_t, 16>& arr)
{
    size_t result = 0;
    const size_t prime = 31;
    for (const auto & item : arr) {
        result = item + (result * prime);
    }
    return result;
}


size_t chu::hashArr(const std::array<uint8_t, 13>& arr)
{
    size_t result = 0;
    const size_t prime = 31;
    for (const auto & item : arr) {
        result = item + (result * prime);
    }
    return result;
}


size_t chu::hashVec(const std::vector<uint8_t> &vec)
{
    size_t result = 0;
    const size_t prime = 31;
    for (const auto & item : vec) {
        result = item + (result * prime);
    }
    return result;
}
