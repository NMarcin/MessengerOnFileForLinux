#pragma once

#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"
#include <iostream>

namespace
{
std::string getUser()
{
    std::string user = getenv("USER");
    return (user == "ciGitlab") ? "root" : user;
}

void simulationOfRunningMessengerProcess()
{
    const std::string command = "../ChatControl/test/messenger_binar &";
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
