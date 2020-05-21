
#pragma once

#include <mxf_exploring/KLV.hpp>
#include <mxf_exploring/Stream.hpp>
#include <mxf_exploring/TimeCodeStamp.hpp>


namespace chu
{

    class SystemItem
    {
    private:
        chu::KeyAndBerLength _keyAndBerLength;

        uint8_t _systemBitmap;
        double_t _packageRate;
        chu::TimeCodeStamp _timeCode;

    public:
        static std::array<uint8_t, 13> ULKeyBytes1;
        static std::array<uint8_t, 13> ULKeyBytes2;

        static bool itIsThis(const chu::Key& key);

        explicit SystemItem(const chu::KeyAndBerLength& keyAndBerLength);
        ~SystemItem() = default;

        size_t posToData() const;
        size_t dataLen() const;
        void parseFields(chu::Stream& dataStream);

        bool hasBitInBitmap(uint8_t bitMask) const;
        chu::TimeCodeStamp timeCode() const;
    };

}
