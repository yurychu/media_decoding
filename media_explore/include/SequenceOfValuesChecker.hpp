//
// Created by yurychu on 15.03.2021.
//

#pragma once

#include <map>

#include <DurationRule.hpp>
#include <CheckReport.hpp>
#include <ValueCounter.hpp>


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
    CheckReport check(const T& value);

private:
    bool accepted(const T& value) const;
    CheckReport handleRules();

};


template<typename T>
void SequenceOfValuesChecker<T>::addRule(const T& value, const DurationRule &rule)
{
    _rules.insert(std::pair<T, DurationRule>{ value, rule });
}


template<typename T>
CheckReport SequenceOfValuesChecker<T>::check(const T& value)
{
    if (!accepted(value)) {
        return CheckReport(ReportType::REJECTED);
    }

    if (_currentValueCounter.isSame(value)) {
        _currentValueCounter.plusOneMoreTime();
    }
    else {
        _currentValueCounter.updateTarget(value);
    }

    return handleRules();
}


template<typename T>
bool SequenceOfValuesChecker<T>::accepted(const T& value) const
{
    return _rules.count(value) > 0;
}


template<typename T>
CheckReport SequenceOfValuesChecker<T>::handleRules()
{
    CheckReport result {ReportType::HANDLED};
    auto range = _rules.equal_range(_currentValueCounter.getValue());
    for (auto it = range.first; it != range.second; ++it){
        const auto ruleReport = it->second.ruleReport(_currentValueCounter.getCount());
        if (!ruleReport.empty()){
            result.addRuleReport(ruleReport);  // just one
            _currentValueCounter.reset();  // set getCount to Zero
            break;
        }
    }
    return result;
}
