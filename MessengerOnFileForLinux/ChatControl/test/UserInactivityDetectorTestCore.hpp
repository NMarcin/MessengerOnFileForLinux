#pragma once

#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"

class UserInactivityDetectorFixture : public ::testing::Test
{
public:
    std::string getUser()
    {
        if(strlen(getenv("USER")))
        {
            return getenv("USER");
        }
        else
        {
            return "root";
        }
    }

    UserInactivityDetectorFixture() : userInactivityDetector_(getUser())   {}

    void SetUp(){}
    void TearDown(){}
    ~UserInactivityDetectorFixture(){}

    UserInactivityDetector userInactivityDetector_;
};
