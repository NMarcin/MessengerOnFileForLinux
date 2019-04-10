#include <StringSum.hpp>



void StringSumSquareBrackets::sum(const std::string& s)
{
    std::string logSum = "StringSumSquareBrackets::sum() started with s = " + s;
    _log.function(logSum);
    _sumedString += "[" + s + "]";
}

std::string StringSumSquareBrackets::getSumedString() const
{
    std::string logData = "StringSumSquareBrackets::getSumedString() sumedString ==" + _sumedString;
    _log.info(logData);
    return _sumedString;
}
