#include <iostream>

#include <User.hpp>
#include <FileHandling.hpp>

User::User()
{
    log.info("User() C-TOR");
}

User::User(std::string username)
        : username_(username)
{
    log.info("User(username) C-TOR");
}

User::~User()
{
    log.info("User D-TOR");
}

std::string User::getPassword() const
{
    log.info("User::getPassword()");
    return password_;
}

std::string User::getUsername() const
{
    log.info("User::getUsername()");
    return username_;
}

int User::getUserPid() const
{
    log.info("User::getUserPid() started");
    //TODO mwozniak czemu nazwa procesu jest skrocona?
    std::string command = "ps -u " + getUsername() + " | grep 'messenger_binar'";
    std::string commandOutput = System::getStdoutFromCommand(command);
    int userPid = atoi(commandOutput.c_str());

    if (0 == userPid)
    {
        log.info("User::getUserPid() ERROR: atoi() failed");
        return 0;
    }

    return userPid;
}

void User::setPassword(const std::string& password)
{
    log.info("User::setPassword()");
    password_ = password;
}

void User::setUsername(const std::string& username)
{
    log.info("User::setUsername()");
    username_ = username;
}
