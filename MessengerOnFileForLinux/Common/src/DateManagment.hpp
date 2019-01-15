#pragma once

#include <chrono>
#include <string>

namespace DataManagment
{
    const time_t getActualDate();
    std::string convertDateToString(const std::time_t&);
}

