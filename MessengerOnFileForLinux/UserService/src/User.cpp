#include <User.hpp>
#include <FileHandling.hpp>

#include <iostream>

User::User()
{
    //NOOP
}

User::User(std::string username)
        : username_(username)
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
    return username_;
}

int User::getUserProcessIdFromSystem() const
{
    //TODO czemu nazwa procesu jest skrocona?
    std::string command = "ps -u " + getUsername() + " | grep 'messenger_binar'";
    std::string commandOutput = getStdoutFromCommand(command);
    std::string userProcessId;

    for (auto& x : commandOutput)
    {
        if (' ' == x)
        {
            return std::atoi(userProcessId.c_str());
        }

        userProcessId += x;
    }

    return std::atoi(userProcessId.c_str());
}


void User::setPassword(const std::string& password)
{
    password_ = password;
}

void User::setUsername(const std::string& username)
{
    username_ = username;
}
