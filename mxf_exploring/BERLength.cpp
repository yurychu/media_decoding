
#include <mxf_exploring/BERLength.hpp>

#include <cstdint>


chu::BERLength::BERLength(uint8_t firstByte)
    : _firstByte {firstByte},
      _sizeValue {0}
{

}

bool chu::BERLength::isLongForm() const
{
    return (_firstByte & 0x80u) != 0;
}

size_t chu::BERLength::sizeValue() const
{
    if (isLongForm()){
        return _sizeValue;
    }
    return _firstByte;
}

uint32_t chu::BERLength::numBytesToDecode() const
{
    uint32_t result = 0;
    result = _firstByte & 0x7fu;
    return result;
}

void chu::BERLength::addByte(uint8_t byte)
{
    _sizeValue <<= 8u;
    _sizeValue |= byte;
}
