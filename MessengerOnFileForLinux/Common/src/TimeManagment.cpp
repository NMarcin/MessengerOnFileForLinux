#include "TimeManagment.hpp"

#include <cstring>
#include <sstream>
#include <iomanip>

const std::tm* TimeManagment::getLocalTime()
{
    const auto time = Time::to_time_t(Time::now());
    return std::localtime(&time);
}

std::string TimeManagment::convertTimeToString(const std::tm* time)
{
    std::ostringstream timeAsString;
    const std::string timeFormat = "%Y-%m-%d %H:%M:%S";
    timeAsString << std::put_time(time, timeFormat.c_str());

    return timeAsString.str();
}
