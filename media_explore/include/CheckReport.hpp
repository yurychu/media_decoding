//
// Created by yurychu on 22.03.2021.
//

#pragma once

#include <string>
#include <memory>


enum class ReportType
{
    EMPTY,
    REJECTED,
    HANDLED
};


class CheckReport
{
private:
    ReportType _reportType;
    std::unique_ptr<std::string> _ruleReport;

public:
    CheckReport();
    explicit CheckReport(const ReportType& reportType);
    CheckReport(const CheckReport& that);
    CheckReport& operator=(const CheckReport& that);
    ~CheckReport() = default;

    bool empty() const;
    std::string str() const;
    void addRuleReport(const std::string& report);
};
