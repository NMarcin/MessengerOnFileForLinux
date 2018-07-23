#pragma once
#include <string>

#include <Logger.hpp>
#include <LogSpace.hpp>

class User
{
public:
    std::string getUsername() const;
    std::string getPassword() const;
    void setPassword(const std::string & password);
    void setUsername(const std::string & username);

    User(std::string username);
    User();
    ~User();

private:
    std::string username_;
    std::string password_;

    Logger log {LogSpace::UserService};
};
