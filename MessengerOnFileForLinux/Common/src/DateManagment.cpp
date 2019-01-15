#include "DateManagment.hpp"

#include <ctime>

namespace DataManagment
{

using std::chrono::system_clock;

const std::time_t getActualDate()
{
    return system_clock::to_time_t(system_clock::now());
}

std::string convertDateToString(const std::time_t& date)
{
    auto constexpr dateSize = 21;
    auto constexpr dateFormat = "%Y-%m-%d %H:%M:%S";
    std::string dateAsString (dateSize, '\0');
    std::strftime(dateAsString.data(), dateAsString.size(), dateFormat, std::localtime(&date));
    return dateAsString;
}
}
