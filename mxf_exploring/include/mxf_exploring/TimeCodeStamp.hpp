
#pragma once

#include <cstdint>
#include <cmath>
#include <vector>
#include <string>

#include <mxf_exploring/ContinuityResult.hpp>


namespace chu
{

    class TimeCodeStamp
    {
    private:
        double_t _frameRate;

        uint32_t _year;
        uint8_t _month;
        uint8_t _day;
        uint8_t _hour;
        uint8_t _minute;
        uint8_t _second;
        uint8_t _frame;
        uint8_t _field;
        uint8_t _fullFrame;

        bool _dropFrame;
        bool _hasFields;
        bool _dropRate;

    public:
        TimeCodeStamp();
        ~TimeCodeStamp() = default;

        static chu::ContinuityResult testContinuity(const std::vector<chu::TimeCodeStamp>& timeCodes);

        void frameRate(double_t rate, bool dropRate);

        void parseFromBcd(const std::vector<uint8_t>& bytes);

        std::string str() const;

        chu::TimeCodeStamp generateNext() const;
        void convertToDrop();
        bool isEqual(const chu::TimeCodeStamp& other) const;
        bool hasDropNumbering() const;

    };

}
