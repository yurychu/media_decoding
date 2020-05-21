
#include <mxf_exploring/FileStream.hpp>

#include <iostream>


chu::FileStream::FileStream(std::string fileName)
    : _fileName(std::move(fileName))
{
    _ifstream.open(_fileName, std::ios::binary);
    if (!_ifstream.is_open()){
        const std::string msg = "Fail open: " + _fileName;
        throw std::runtime_error(msg);
    }
}

chu::PartOfStream chu::FileStream::readOrEmpty(size_t numBytes)
{
    std::vector<StreamType::char_type> buff (numBytes);
    auto offset = _ifstream.tellg();
    if (offset < 0){
        const std::string msg = "Fail tellg() for stream: " + _fileName;
        throw std::runtime_error(msg);
    }
    _ifstream.read(buff.data(), buff.size());

    if (_ifstream.gcount() != numBytes){
        return chu::PartOfStream();
    }

    return chu::PartOfStream {buff, static_cast<size_t>(offset) };
}

bool chu::FileStream::valid() const
{
    return _ifstream.good();
}

void chu::FileStream::skipBytes(size_t numBytes)
{
    _ifstream.seekg(numBytes, std::ios::cur);
}

void chu::FileStream::reset()
{
    _ifstream.clear();
    _ifstream.seekg(0, std::ios::beg);
    if (_ifstream.tellg() == -1){
        throw std::runtime_error("Fail seek stream, do not support seek");
    }
}

void chu::FileStream::seekToOffset(size_t pos)
{
    _ifstream.seekg(pos, std::iostream::beg);
    if (_ifstream.tellg() != pos){
        throw std::runtime_error("Fail seek to offset in ifstream");
    }
}
