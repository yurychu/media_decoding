
#pragma once

#include <cstdint>
#include <array>

#include <mxf_exploring/PartOfStream.hpp>
#include <mxf_exploring/BERLength.hpp>


namespace chu
{

    class Key
    {
    private:
        chu::PartOfStream _partOfStream;

    public:
        explicit Key(const chu::PartOfStream& part);
        ~Key() = default;

        std::string bytesToStr() const;
        size_t getHash(size_t useNumBytes) const;
        size_t getStreamPos() const;
        size_t lengthInBytes() const;
    };


    class KeyAndBerLength
    {
    private:
        chu::Key _key;
        chu::BERLength _berLength;

    public:
        KeyAndBerLength(const chu::Key& key, const chu::BERLength& berLength);
        ~KeyAndBerLength() = default;

        const chu::Key& key() const;
        const chu::BERLength& berLength() const;

    };

}
