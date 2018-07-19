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

void User::setPassword(const std::string& password)
{
    password_ = password;
}

void User::setUsername(const std::string& username)
{
    username_ = username;
}
