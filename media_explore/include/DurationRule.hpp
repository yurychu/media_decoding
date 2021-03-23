//
// Created by yurychu on 22.03.2021.
//

#pragma once

#include <string>


class DurationRule
{
private:
    // todo y.chu: impelemnt details

public:
    DurationRule() = default;
    ~DurationRule() = default;

    std::string ruleReport(size_t durationValue);
};
