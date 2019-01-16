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
    constexpr auto day = 9;
    constexpr auto month = 2;
    constexpr auto year = 2019;
    std::tm timePoint =
    {
        .tm_sec  = 0,
        .tm_min  = 0,
        .tm_hour = 0,
        .tm_mday = (day),
        .tm_mon  = (month) - 1,
        .tm_year = (year) - 1900,
    };
    using Time = std::chrono::system_clock;
    const auto time = Time::from_time_t(std::mktime(&timePoint));
    const auto timeAsString = TimeManagment::convertTimeToString(Time::to_time_t(time));
    std::string expectedTimeValue = "2019-02-09 00:00:00";
    EXPECT_EQ(timeAsString, expectedTimeValue);
}
