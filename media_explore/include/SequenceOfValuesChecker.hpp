//
// Created by yurychu on 15.03.2021.
//

#pragma once

#include <DurationRule.hpp>
#include <CheckReport.hpp>
#include <ValueCounter.hpp>

#include <map>


template<typename T>
class SequenceOfValuesChecker
{
private:
    std::multimap<T, DurationRule> _rules;
    ValueCounter<T> _currentValueCounter;

public:
    SequenceOfValuesChecker() = default;
    ~SequenceOfValuesChecker() = default;

    void addRule(const T& value, const DurationRule& rule);
    CheckReport check(const T& value) const;

private:
    bool accepted(const T& value) const;

};


template<typename T>
void SequenceOfValuesChecker<T>::addRule(const T& value, const DurationRule &rule)
{
    _rules.insert(std::pair<T, DurationRule>{ value, rule });
}


template<typename T>
CheckReport SequenceOfValuesChecker<T>::check(const T& value) const
{
    if (!accepted(value)){
        return CheckReport(ReportType::REJECTED);
    }
    else {
        auto isSame = _currentValueCounter.isSame(value);
    }
    return CheckReport();
}


template<typename T>
bool SequenceOfValuesChecker<T>::accepted(const T& value) const
{
    return _rules.count(value) > 0;
}
