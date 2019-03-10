#pragma once

#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"
#include <iostream>

class UserInactivityDetectorFixture : public ::testing::Test
{
public:
    std::string getUser()
    {
        if(getenv("USER") =="ciGitlab")
        {
            std::cout << "TUTAJ" << std::endl;
            std::cout << getenv("USER") << std::endl;
            return "root";

        }
        else
        {
            std::cout << "TAM" << std::endl;
            std::cout << getenv("USER") << std::endl;
            return getenv("USER");
        }
    }

    UserInactivityDetectorFixture() : userInactivityDetector_(getUser())   {}

    void SetUp(){}
    void TearDown(){}
    ~UserInactivityDetectorFixture(){}

    UserInactivityDetector userInactivityDetector_;
};
