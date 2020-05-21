
#pragma once

#include <string>
#include <fstream>

#include <mxf_exploring/Stream.hpp>


namespace chu
{

    class FileStream : public chu::Stream
    {
    private:
        using StreamType = std::ifstream;
        std::string _fileName;
        StreamType _ifstream;

    public:
        explicit FileStream(std::string fileName);
        ~FileStream() override = default;

        bool valid() const override;

        chu::PartOfStream readOrEmpty(size_t numBytes) override;
        void skipBytes(size_t numBytes) override;
        void reset() override;
        void seekToOffset(size_t pos) override;

    };


}
