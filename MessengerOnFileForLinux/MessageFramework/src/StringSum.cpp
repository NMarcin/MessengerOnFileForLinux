#include <StringSum.hpp>



void StringSumSquareBrackets::sum(const std::string& s)
{
    std::string logSum = "StringSumSquareBrackets::sum() started with s = " + s;
    log_.function(logSum);
    sumedString += "[" + s + "]";
}

std::string StringSumSquareBrackets::getSumedString() const
{
    std::string logData = "StringSumSquareBrackets::getSumedString() sumedString ==" + sumedString;
    log_.info(logData);
    return sumedString;
}
