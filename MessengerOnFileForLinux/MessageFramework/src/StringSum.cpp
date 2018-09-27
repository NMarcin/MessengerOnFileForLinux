#include <StringSum.hpp>



void StringSumSquareBrackets::sum(std::string s)
{
    sumedString += "[" + s + "]";
}

std::string StringSumSquareBrackets::getSumedString()
{
    std::string logData = "StringSumSquareBrackets::getSumedString() sumedString ==" + sumedString;
    log_.info(logData);
    return sumedString;
}
