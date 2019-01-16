#include <gtest/gtest.h>
#include <ctime>
#include <regex>
#include <iostream>

#include "TimeManagment.hpp"

TEST(ConvertTimeToString, TimeFormatSizeIsNineteen)
{
    const auto timeAsString = TimeManagment::convertTimeToString(TimeManagment::getActualDate());
    constexpr auto expectedTimeSize = 19;
    EXPECT_EQ(timeAsString.size(), expectedTimeSize);
}

TEST(ConvertTimeToString, TimeFormatIsCorrect)
{
    const auto unixEpochTimeAsString = TimeManagment::convertTimeToString(std::time_t{});
    std::regex expectedTimeFormat("([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})");
    std::smatch matcher;
    EXPECT_TRUE(std::regex_search(unixEpochTimeAsString, matcher, expectedTimeFormat));
}

TEST(ConvertTimeToString, TimeValueIsCorrect)
{
    const auto unixEpochTimeAsString = TimeManagment::convertTimeToString(std::time_t{});
    std::string expectedTimeValue = "1970-01-01 01:00:00";
    EXPECT_EQ(unixEpochTimeAsString, expectedTimeValue);
}
