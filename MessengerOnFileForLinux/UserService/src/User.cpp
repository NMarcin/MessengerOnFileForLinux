#include <iostream>

#include <User.hpp>
#include <FileHandling.hpp>

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

int User::getUserPid() const
{
    //TODO mwozniak czemu nazwa procesu jest skrocona?
    std::string command = "ps -u " + getUsername() + " | grep 'messenger_binar'";
    std::string commandOutput = System::getStdoutFromCommand(command);
    int userPid = atoi(commandOutput.c_str());

    if (0 == userPid)
    {
        return 0;
    }

    return userPid;
}


void User::setPassword(const std::string& password)
{
    password_ = password;
}

void User::setUsername(const std::string& username)
{
    username_ = username;
}
