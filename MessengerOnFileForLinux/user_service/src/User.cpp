#include "User.hpp"
#include "FileHandling.hpp"

User::User()
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

void User::setPassword(const std::string & password)
{
    password_ = password;
}

void User::setUsername(const std::string & password)
{
    password_ = password;
}
