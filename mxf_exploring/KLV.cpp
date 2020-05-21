
#include <mxf_exploring/KLV.hpp>

#include <sstream>
#include <iomanip>

#include <mxf_exploring/Hasher.hpp>


chu::Key::Key(const chu::PartOfStream& part)
    : _partOfStream(part)
{

}

std::string chu::Key::bytesToStr() const
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    const auto & buff = _partOfStream.buffer();
    for (const auto & ch : buff){
        ss << std::setw(2) << (uint32_t)ch << '.';
    }
    return ss.str();
}

size_t chu::Key::getHash(size_t useNumBytes) const
{
    auto tmpBuff = _partOfStream.buffer();
    tmpBuff.resize(useNumBytes);
    return chu::hashVec(tmpBuff);
}

size_t chu::Key::getStreamPos() const
{
    return _partOfStream.offset();
}

size_t chu::Key::lengthInBytes() const
{
    return _partOfStream.size();
}


chu::KeyAndBerLength::KeyAndBerLength(const chu::Key& key, const chu::BERLength& berLength)
    : _key(key),
      _berLength(berLength)
{

}

const chu::Key& chu::KeyAndBerLength::key() const
{
    return _key;
}

const chu::BERLength& chu::KeyAndBerLength::berLength() const
{
    return _berLength;
}
