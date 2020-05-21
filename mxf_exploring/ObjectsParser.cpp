
#include <mxf_exploring/ObjectsParser.hpp>


chu::ObjectsParser::ObjectsParser(chu::Stream &dataStream)
    : _stopReadingFlag(false),
      _dataStream(dataStream)
{

}

void chu::ObjectsParser::parseObjects()
{
    _dataStream.reset();
    do {
        auto key = readKey();
        if (_stopReadingFlag){
            break;
        }
        auto berLength = readLength();
        chu::KeyAndBerLength kAndL {key, berLength};
        readData(kAndL);
    } while (_dataStream.valid());
}

chu::Key chu::ObjectsParser::readKey()
{
    auto streamPart = _dataStream.readOrEmpty(16);
    if (streamPart.empty()){
        _stopReadingFlag = true;
    }
    return chu::Key {streamPart};
}

chu::BERLength chu::ObjectsParser::readLength()
{
    auto streamPart = _dataStream.readOrEmpty(1);
    if (streamPart.empty()){
        throw std::runtime_error("Fail read length after key in file");
    }

    auto berLength = chu::BERLength {streamPart.buffer().at(0)};
    if (berLength.isLongForm()){
        streamPart = _dataStream.readOrEmpty(berLength.numBytesToDecode());
        if (streamPart.empty()){
            throw std::runtime_error("Fail read full length parts after key in file");
        }
        for (const auto & byte : streamPart.buffer()){
            berLength.addByte(byte);
        }
    }

    return berLength;
}

void chu::ObjectsParser::readData(const chu::KeyAndBerLength &keyAndBerLength)
{
    if (chu::SystemItem::itIsThis(keyAndBerLength.key())){
        chu::SystemItem sysItem {keyAndBerLength};
        sysItem.parseFields(_dataStream);
        _sysItems.emplace_back(sysItem);
    }
    else {
        _dataStream.skipBytes(keyAndBerLength.berLength().sizeValue());
    }

}

std::vector<chu::TimeCodeStamp> chu::ObjectsParser::extractTimeCodes() const
{
    constexpr uint8_t userDateTimeBit = 0x10;
    std::vector<chu::TimeCodeStamp> results;
    for (const auto & item : _sysItems){
        if (item.hasBitInBitmap(userDateTimeBit)){
            results.emplace_back(item.timeCode());
        }
    }
    return results;
}
