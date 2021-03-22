//
// Created by yurychu on 15.03.2021.
//

#pragma once

#include <DurationRule.hpp>
#include <CheckReport.hpp>

#include <vector>


class SequenceOfValuesChecker
{
private:
    std::vector<DurationRule> _rules;

public:
    SequenceOfValuesChecker() = default;
    ~SequenceOfValuesChecker() = default;

    void addRule(DurationRule durationRule);

    CheckReport check() const;

};

