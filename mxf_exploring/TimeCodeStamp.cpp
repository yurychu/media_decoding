
#include <mxf_exploring/TimeCodeStamp.hpp>

#include <sstream>
#include <iomanip>

#include <mxf_exploring/ParserBCD.hpp>


chu::TimeCodeStamp::TimeCodeStamp()
    : _frameRate(0),
      _year(0),
      _month(0),
      _day(0),
      _hour(0),
      _minute(0),
      _second(0),
      _frame(0),
      _field(0),
      _fullFrame(0),
      _dropFrame(false),
      _hasFields(false),
      _dropRate{false}
{

}

void chu::TimeCodeStamp::frameRate(double_t rate, bool dropRate)
{
    _frameRate = rate;
    _dropRate = dropRate;
}

void chu::TimeCodeStamp::parseFromBcd(const std::vector<uint8_t>& bytes)
{
    uint8_t frameB = bytes.at(1);
    uint8_t secondB = bytes.at(2);
    uint8_t minuteB = bytes.at(3);
    uint8_t hourB = bytes.at(4);
    uint8_t dayB = bytes.at(5);
    uint8_t monthB = bytes.at(6);
    uint8_t yearB = bytes.at(7);

    // bit mask manipulations to parse BCD, from mxf inspect source code
    _hour = chu::parseBCDtc(hourB, 0x30);
    _minute = chu::parseBCDtc(minuteB, 0x70);
    _second = chu::parseBCDtc(secondB, 0x70);
    _frame = chu::parseBCDtc(frameB, 0x30);
    _dropFrame = (frameB & 0x40u) == 0x40;

    if (_frameRate >= 59) {
        if ((secondB & 0x80u) == 0x80){
            _field = 1;
        }
        _fullFrame = (_frame * 2) + _field;
        _hasFields = true;
    }
    else if (_frameRate >= 49) {
        if ((hourB & 0x80u) == 0x80){
            _field = 1;
        }
        _fullFrame = (_frame * 2) + _field;
        _hasFields = true;
    }
    else {
        _fullFrame = _frame;
        _hasFields = false;
    }

    _day = parseBCDtc(dayB, 0x30);  // binary group data BG1 + BG2
    _month = parseBCDtc(monthB, 0x10); // binary group data BG3 + BG4
    _year = parseBCDtc(yearB, 0xF0); // binary group data BG5 + BG6
}

std::string chu::TimeCodeStamp::str() const
{
    std::stringstream result;

    result << std::setfill('0');

    result << std::setw(2) << (uint32_t)_hour << ":";
    result << std::setw(2) << (uint32_t)_minute << ":";
    result << std::setw(2) << (uint32_t)_second << ":";
    result << std::setw(2) << (uint32_t)_frame;

    return result.str();
}

chu::ContinuityResult chu::TimeCodeStamp::testContinuity(const std::vector<chu::TimeCodeStamp>& timeCodes)
{
    chu::ContinuityResult result;
    if (timeCodes.empty()) {
        return result;
    }

    auto it1 = timeCodes.cbegin();
    auto it2 = it1 + 1;
    for (; it2 != timeCodes.end(); ++it1, ++it2) {
        auto expected = it1->generateNext();
        if (!it2->isEqual(expected)) {
            expected.convertToDrop();
            if (!it2->isEqual(expected)) {
                std::string msg = "Next TimeCode not equal expected continuity. From: "
                                  + it1->str() + " to: " + it2->str()
                                  + " where expected: " + expected.str();
                result.setFail(msg);
                return result;
            }
        }
        result.update();
    }

    return result;
}

chu::TimeCodeStamp chu::TimeCodeStamp::generateNext() const
{
    chu::TimeCodeStamp resTc {*this };
    resTc._frame++;
    if (resTc._frame >= resTc._frameRate) {
        resTc._frame = 0;
        resTc._second++;
        if (resTc._second > 59) {
            resTc._second = 0;
            resTc._minute++;
            if (resTc._minute > 59) {
                resTc._minute = 0;
                resTc._hour++;
            }
        }
    }
    return resTc;
}

bool chu::TimeCodeStamp::isEqual(const chu::TimeCodeStamp& other) const
{
    return _frame == other._frame
           && _second == other._second
           && _minute == other._minute
           && _hour == other._hour;
}

bool chu::TimeCodeStamp::hasDropNumbering() const
{
    return _dropRate;
}

void chu::TimeCodeStamp::convertToDrop()
{
    if (hasDropNumbering()) {
        if (_minute % 10) {
            if (_second == 0 && _frame == 0) {
                _frame = 2;
            }
        }
    }
}
