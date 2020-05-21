
#pragma once

#include <cstdint>
#include <cstddef>

namespace chu
{

    class BERLength
    {
    private:
        uint8_t _firstByte;
        size_t _sizeValue;

    public:
        BERLength(uint8_t firstByte);
        ~BERLength() = default;

        bool isLongForm() const;
        uint32_t numBytesToDecode() const;

        void addByte(uint8_t byte);

        size_t sizeValue() const;

    };

}
