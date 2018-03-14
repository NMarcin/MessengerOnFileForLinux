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

int User::getPidFormString(const std::string& commandOutput) const
{
    std::string pid;

    for (auto& x : commandOutput)
    {
        if (' ' == x && !pid.empty())
        {
            return std::atoi(pid.c_str());
        }

        pid += x;
    }

    return 0; //TODO mwozniak error
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
    int userPid = getPidFormString(commandOutput);

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
