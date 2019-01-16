#include "TimeManagment.hpp"

#include <ctime>
#include <algorithm>

namespace
{
void removeEmptyCharactersFromTimeEnd(std::string& date)
{
   date.pop_back();
   date.pop_back();
}
}

namespace TimeManagment
{

using Time = std::chrono::system_clock;

const std::time_t getActualDate()
{
    return Time::to_time_t(Time::now());
}

std::string convertTimeToString(const std::time_t& time)
{
    auto constexpr theLeastAcceptableTimeBuffer = 21;
    auto constexpr timeFormat = "%Y-%m-%d %H:%M:%S";
    std::string timeAsString (theLeastAcceptableTimeBuffer, '\0');
    std::strftime(timeAsString.data(), timeAsString.size(), timeFormat, std::localtime(&time));
    removeEmptyCharactersFromTimeEnd(timeAsString);
    return timeAsString;
}
}
