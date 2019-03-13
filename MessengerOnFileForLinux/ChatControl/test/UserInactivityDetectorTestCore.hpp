#pragma once

#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"

namespace
{
std::string getUser()
{
    std::string user = getenv("USER");
    if(user == "ciGitlab")
    {
        return "root";
    }
    else
    {
        return user;
    }
}

void simulationOfRunningMessengerProcess()
{
    const std::string command = "../scripts/messenger_binar &";
    system(command.c_str());
}
}//namespace

class UserInactivityDetectorFixture : public ::testing::Test
{
public:
    UserInactivityDetectorFixture() : userInactivityDetector_(getUser())
    {
        simulationOfRunningMessengerProcess();
    }
    void SetUp(){}
    void TearDown(){}
    ~UserInactivityDetectorFixture(){}

    UserInactivityDetector userInactivityDetector_;
};
