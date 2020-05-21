
#include <mxf_exploring/PartOfStream.hpp>


chu::PartOfStream::PartOfStream()
    : _buffer{},
      _streamOffset(0)
{

}

chu::PartOfStream::PartOfStream(const std::vector<char> & buff, size_t streamOffset)
    : _buffer{buff.begin(), buff.end()},
      _streamOffset(streamOffset)
{

}

bool chu::PartOfStream::empty() const
{
    return buffer().empty();
}

const chu::PartOfStream::BufferType& chu::PartOfStream::buffer() const
{
    return _buffer;
}

size_t chu::PartOfStream::offset() const
{
    return _streamOffset;
}

size_t chu::PartOfStream::size() const
{
    return buffer().size();
}

std::vector<uint8_t> chu::PartOfStream::getBytesFrom(size_t pos, size_t numBytes) const
{
    std::vector<uint8_t> result;

    for (size_t i = 0; i < numBytes; ++i){
        result.emplace_back(buffer().at(pos + i));
    }

    return result;
}
