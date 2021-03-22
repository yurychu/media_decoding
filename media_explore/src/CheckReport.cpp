//
// Created by yurychu on 22.03.2021.
//

#include <CheckReport.hpp>


CheckReport::CheckReport()
    : _reportType{ReportType::EMPTY}
{

}


CheckReport::CheckReport(const ReportType &reportType)
        : _reportType{reportType}
{

}


bool CheckReport::empty() const
{
    return _reportType == ReportType::EMPTY;
}


std::string CheckReport::str() const
{
    return "report str";
}

