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
<<<<<<< HEAD
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
            return getenv("USER");
        }
    }

    UserInactivityDetectorFixture() : userInactivityDetector_(getUser())
    {
        auto x = new int(5);
        std::string command = "../scripts/messenger_binar &";
        system(command.c_str());
    }

=======
    UserInactivityDetectorFixture() : userInactivityDetector_(getUser())
    {
        simulationOfRunningMessengerProcess();
    }
>>>>>>> 415b7f27a6eb944f4de6d599bbe1c922ba58a5d9
    void SetUp(){}
    void TearDown(){}
    ~UserInactivityDetectorFixture(){}

    UserInactivityDetector userInactivityDetector_;
};
