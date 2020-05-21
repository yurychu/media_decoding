
#include <mxf_exploring/IndexTableSegment.hpp>

#include <iostream>


std::array<uint8_t, 16> chu::IndexTableSegment::ULKeyBytes = {
        0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x02, 0x01, 0x01, 0x10, 0x01, 0x00
};

chu::IndexTableSegment::IndexTableSegment(const chu::KeyAndBerLength &keyAndBerLength)
    : _keyAndBerLength(keyAndBerLength)
{

}

size_t chu::IndexTableSegment::posToData() const
{
    size_t result = 0;

    result = _keyAndBerLength.key().getStreamPos();
    result += _keyAndBerLength.key().lengthInBytes();
    result += _keyAndBerLength.berLength().numBytesToDecode();
    result += 1;  // first byte of ber length

    return result;
}

size_t chu::IndexTableSegment::dataLen() const
{
    return _keyAndBerLength.berLength().sizeValue();
}

void chu::IndexTableSegment::parseFields(chu::Stream &dataStream)
{
    // todo: LocalTag parsing
}
