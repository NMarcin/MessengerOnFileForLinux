#include <StringSum.hpp>



void StringSumSquareBrackets::sum(std::string s)
{
    sumedString += "[" + s + "]";
}

std::string StringSumSquareBrackets::getSumedString()
{
    return sumedString;
}
