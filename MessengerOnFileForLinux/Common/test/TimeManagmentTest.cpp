#include <gtest/gtest.h>
#include <ctime>
#include <regex>
#include <iostream>

#include "TimeManagment.hpp"

namespace
{
const std::tm* getUnixEpochTime()
{
    const auto time = std::time_t{};
    return std::gmtime(&time);
}
}//namespace

TEST(ConvertTimeToString, TimeFormatSizeIsNineteen)
{
    constexpr int expectedTimeSize = 19;
    const std::string timeAsString = TimeManagment::convertTimeToString(TimeManagment::getLocalTime());

    EXPECT_EQ(timeAsString.size(), expectedTimeSize);
}

TEST(ConvertTimeToString, TimeFormatIsCorrect)
{   
    const std::regex expectedTimeFormat("([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})");
    std::smatch matcher;
    const auto unixEpochTimeAsString = TimeManagment::convertTimeToString(TimeManagment::getLocalTime());

    EXPECT_TRUE(std::regex_search(unixEpochTimeAsString, matcher, expectedTimeFormat));
}

TEST(ConvertTimeToString, TimeValueIsCorrect)
{  
    const std::string expectedTimeValue = "1970-01-01 00:00:00";
    const std::string unixEpochTimeAsString = TimeManagment::convertTimeToString(getUnixEpochTime());

    EXPECT_EQ(unixEpochTimeAsString, expectedTimeValue);
}
