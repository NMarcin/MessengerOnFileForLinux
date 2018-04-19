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
    log.info("User(std::string username) C-TOR");
}

User::~User()
{
    log.info("User D-TOR");
}

std::string User::getPassword() const
{
    return password_;
}

std::string User::getUsername() const
{
    return username_;
}

/*
int User::getUserPid() const
{
    log.info("User::getUserPid() started");
    //TODO mwozniak czemu nazwa procesu jest skrocona?
    std::string command = "ps -u " + getUsername() + " | grep 'messenger_binar'";   // TODO remember to change messenger_binar when binary name will change
    std::string commandOutput = ConsolControl::getStdoutFromCommand(command);
    int userPid = atoi(commandOutput.c_str());

    if (0 == userPid)
    {
        log.info("User::getUserPid() ERROR: atoi() failed");
        return 0;
    }

    return userPid;
}
*/
void User::setPassword(const std::string& password)
{
    password_ = password;
}

void User::setUsername(const std::string& username)
{
    username_ = username;
}
