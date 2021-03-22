//
// Created by yurychu on 22.03.2021.
//

#pragma once

#include <string>

enum class ReportType
{
    EMPTY,
    REJECTED
};


class CheckReport
{
private:
    ReportType _reportType;

public:
    CheckReport();
    explicit CheckReport(const ReportType& reportType);
    ~CheckReport() = default;

    bool empty() const;

    std::string str() const;
};



