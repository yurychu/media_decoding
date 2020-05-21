
#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>


namespace chu
{

    class PartOfStream
    {
    private:
        using BufferType = std::vector<uint8_t>;
        BufferType _buffer;
        size_t _streamOffset;

    public:
        const BufferType& buffer() const;

    public:
        PartOfStream();
        PartOfStream(const std::vector<char>& buff, size_t streamOffset);
        ~PartOfStream() = default;

        size_t offset() const;
        bool empty() const;
        size_t size() const;

        std::vector<uint8_t> getBytesFrom(size_t pos, size_t numBytes) const;

    };

}
