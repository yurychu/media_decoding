
#pragma once

#include <atomic>

#include <mxf_exploring/Stream.hpp>
#include <mxf_exploring/KLV.hpp>
#include <mxf_exploring/SystemItem.hpp>


namespace chu
{

    class ObjectsParser
    {
    private:
        bool _stopReadingFlag;
        chu::Stream& _dataStream;

        std::vector<chu::SystemItem> _sysItems;

        chu::Key readKey();
        chu::BERLength readLength();
        void readData(const chu::KeyAndBerLength& keyAndBerLength);

    public:
        explicit ObjectsParser(chu::Stream& dataStream);
        ~ObjectsParser() = default;

        void parseObjects();

        std::vector<chu::TimeCodeStamp> extractTimeCodes() const;

    };

}
