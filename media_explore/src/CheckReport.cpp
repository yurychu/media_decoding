//
// Created by yurychu on 22.03.2021.
//

#include <CheckReport.hpp>


CheckReport::CheckReport()
    : _reportType{ReportType::EMPTY},
    _ruleReport{nullptr}
{

}


CheckReport::CheckReport(const ReportType &reportType)
        : _reportType{reportType},
        _ruleReport{nullptr}
{

}


CheckReport::CheckReport(const CheckReport &that)
{
    _reportType = that._reportType;
    _ruleReport = std::make_unique<std::string>(*that._ruleReport);
}


CheckReport &CheckReport::operator=(const CheckReport &that)
{
    if (this != &that){
        _reportType = that._reportType;
        _ruleReport = std::make_unique<std::string>(*that._ruleReport);
    }

    return *this;
}


bool CheckReport::empty() const
{
    return _reportType == ReportType::EMPTY;
}


std::string CheckReport::str() const
{
    if (_ruleReport) {
        return *_ruleReport;
    }
    return "";
}


void CheckReport::addRuleReport(const std::string &report)
{
    _ruleReport = std::make_unique<std::string>(report);
}
