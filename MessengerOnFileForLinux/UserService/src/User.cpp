#include <User.hpp>
#include <FileHandling.hpp>

User::User()
{
    log_.function("User() C-TOR");
}

User::User(std::string username)
        : username_(username)
{
    log_.function("User(std::string username) C-TOR");
}

User::~User()
{
    log_.function("User D-TOR");
}

std::string User::getPassword() const
{
    log_.function("User::getPassword() started");
    return password_;
}

std::string User::getUsername() const
{
    log_.function("User::getUsername() started");
    return username_;
}

void User::setPassword(const std::string& password)
{
    log_.function("User::setPassword() started");
    password_ = password;
}

void User::setUsername(const std::string& username)
{
    log_.function("User::setUsername() started");
    username_ = username;
}
