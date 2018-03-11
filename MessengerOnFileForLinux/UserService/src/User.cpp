#include "User.hpp"
#include "FileHandling.hpp"

#include <iostream>

User::User()
{
    //NOOP
}

User::User(std::string username) :
    username_(username)
{
    //NOOP
}

User::~User()
{
    //NOOP
}

std::string User::getPassword() const
{
    return password_;
}

std::string User::getUsername() const
{
   // if (username_.empty())
 //  {
   //     setUsername(getEnviromentalVariable("USER"));
   // }

    return username_;
}

int User::getUserProcessID() const
{
    return userProcessID_;
}

int User::getUserProcessIdFromSystem() const
{
    //TODO poprawic bo jest brzydko + username w command
    //TODO czemu nazwa procesu jest skrocona?
    std::string command = "ps -u " + getUsername() + " | grep 'messenger_binar'";
    std::string commandOutput = getStdoutFromCommand(command);
    std::string processId;

    for (auto& x : commandOutput)
    {
        int flag = false;
        if (' ' == x)
        {
            if (true == flag)
            {
                break;
            }
            flag = true;
        }

        processId += x;
    }

    return std::atoi(processId.c_str());
}


void User::setPassword(const std::string & password)
{
    password_ = password;
}

void User::setUsername(const std::string & password)
{
    password_ = password;
}

void User::setUserPorcessID(const int userProcessID)
{
    userProcessID_ = userProcessID;
}
