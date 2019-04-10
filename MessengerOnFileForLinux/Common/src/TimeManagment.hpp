#pragma once

#include <chrono>
#include <string>

namespace TimeManagment
{
using Time = std::chrono::system_clock;

const std::tm* getLocalTime();
std::string convertTimeToString(const std::tm* time);

}//TimeManagment
