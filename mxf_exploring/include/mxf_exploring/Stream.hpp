
#pragma once

#include <cstdint>

#include <mxf_exploring/PartOfStream.hpp>


namespace chu
{

    class Stream
    {
    public:
        Stream();
        virtual ~Stream() = 0;

        virtual chu::PartOfStream readOrEmpty(size_t numBytes) = 0;
        virtual void skipBytes(size_t numBytes) = 0;
        virtual void reset() = 0;
        virtual void seekToOffset(size_t pos) = 0;

        virtual bool valid() const = 0;

    };

}
