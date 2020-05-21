
#include <mxf_exploring/SystemItem.hpp>
#include <mxf_exploring/Hasher.hpp>


std::array<uint8_t, 13> chu::SystemItem::ULKeyBytes1 = {
        0x06, 0x0e, 0x2b, 0x34, 0x02, 0x05, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x04};

std::array<uint8_t, 13> chu::SystemItem::ULKeyBytes2 = {
        0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x14};


chu::SystemItem::SystemItem(const chu::KeyAndBerLength& keyAndBerLength)
    : _keyAndBerLength(keyAndBerLength),
      _packageRate(0),
      _timeCode {}
{

}

size_t chu::SystemItem::posToData() const
{
    size_t result = 0;

    result = _keyAndBerLength.key().getStreamPos();
    result += _keyAndBerLength.key().lengthInBytes();
    result += _keyAndBerLength.berLength().numBytesToDecode();
    result += 1;  // first byte of ber length

    return result;
}

size_t chu::SystemItem::dataLen() const
{
    return _keyAndBerLength.berLength().sizeValue();
}

void chu::SystemItem::parseFields(chu::Stream& dataStream)
{
    dataStream.reset();
    dataStream.seekToOffset(posToData());

    auto streamPart = dataStream.readOrEmpty(dataLen());

    if (!streamPart.empty()){
        _systemBitmap = streamPart.getBytesFrom(0, 1).at(0);
        // todo (y.chu): parse all parts on bitmap scheme
    }

    if (streamPart.size() >= 2){
        auto rate = streamPart.getBytesFrom(1, 1).at(0);
        uint32_t rateIdx = (rate & 0x1Eu) >> 1u;  // from "mxf inspect" souce code bit manipulation
        std::array<uint8_t, 16> rates = {0, 24, 25, 30, 48, 50, 60, 72, 75, 90, 96, 100, 120, 0, 0, 0 };
        double_t rateNonDrop = 1;
        if (rateIdx < 16){
            rateNonDrop = rates.at(rateIdx);
        }
        _packageRate = rateNonDrop;
        bool isDropRate = false;
        if ((rate & 0x01u) == 0x01){  // divider active bit (mxf inspect code)
            _packageRate /= 1.001;
            isDropRate = true;
        }
        _timeCode.frameRate(_packageRate, isDropRate);
    }

    if (streamPart.size() >= 57){  // there is TimeCodes
        auto userDateBunchBytes = streamPart.getBytesFrom(40, 17);
        _timeCode.parseFromBcd(userDateBunchBytes);
    }
}

bool chu::SystemItem::itIsThis(const chu::Key & key)
{
    const size_t sysItemKeyHash1 = chu::hashArr(chu::SystemItem::ULKeyBytes1);
    const size_t sysItemKeyHash2 = chu::hashArr(chu::SystemItem::ULKeyBytes2);
    const size_t curKeyHash = key.getHash(chu::SystemItem::ULKeyBytes1.size());

    return sysItemKeyHash1 == curKeyHash || sysItemKeyHash2 == curKeyHash;
}

chu::TimeCodeStamp chu::SystemItem::timeCode() const
{
    return _timeCode;
}

bool chu::SystemItem::hasBitInBitmap(uint8_t bitMask) const
{
    return _systemBitmap & bitMask;
}
