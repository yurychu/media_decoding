
#pragma once

#include <cstdint>
#include <array>

#include <mxf_exploring/KLV.hpp>
#include <mxf_exploring/Stream.hpp>


namespace chu
{

    class IndexTableSegment
    {
    private:
        chu::KeyAndBerLength _keyAndBerLength;

    public:
        static std::array<uint8_t, 16> ULKeyBytes;

        explicit IndexTableSegment(const chu::KeyAndBerLength& keyAndBerLength);
        ~IndexTableSegment() = default;

        size_t posToData() const;
        size_t dataLen() const;
        void parseFields(chu::Stream& dataStream);

    };

}
