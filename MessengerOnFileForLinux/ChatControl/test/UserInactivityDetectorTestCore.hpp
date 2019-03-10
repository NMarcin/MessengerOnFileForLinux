#pragma once

#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"

class UserInactivityDetectorFixture : public ::testing::Test
{
public:
    std::string getUser()
    {
        if(getenv("USER") =="ciGitlab")
        {
            return "root";

        }
        else
        {
            return getenv("USER");
        }
    }

    UserInactivityDetectorFixture() : userInactivityDetector_(getUser())   {}

    void SetUp(){}
    void TearDown(){}
    ~UserInactivityDetectorFixture(){}

    UserInactivityDetector userInactivityDetector_;
};
