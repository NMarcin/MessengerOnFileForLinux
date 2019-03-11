#pragma once

#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"
#include <iostream>

class UserInactivityDetectorFixture : public ::testing::Test
{
public:
    std::string getUser()
    {
        std::string user = getenv("USER");
        if(user =="ciGitlab")
        {
            std::cout << "TUTAJ" << std::endl;
            std::cout << user << std::endl;
            std::cout <<  ":"<<getenv("USER") <<":" << std::endl;
            return "root";

        }
        else
        {
            std::cout << "TAM" << std::endl;
            std::cout << user << std::endl;
            std::cout <<  ":"<<getenv("USER") <<":" << std::endl;
            return "root";
        }
    }

    UserInactivityDetectorFixture() : userInactivityDetector_(getUser())   {}

    void SetUp(){}
    void TearDown(){}
    ~UserInactivityDetectorFixture(){}

    UserInactivityDetector userInactivityDetector_;
};
