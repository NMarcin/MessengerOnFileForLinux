#pragma once

#include <chrono>
#include <string>

namespace TimeManagment
{
    const time_t getActualDate();
    std::string convertTimeToString(const std::time_t&);
}

