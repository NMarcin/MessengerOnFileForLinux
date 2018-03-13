#pragma once
#include <string>

class User
{
public:
    std::string getUsername() const;
    std::string getPassword() const;
    int getUserProcessIdFromSystem() const;
    void setPassword(const std::string & password);
    void setUsername(const std::string & username);

    User(std::string username);
    User();
    ~User();

private:
    std::string username_;
    std::string password_;
};
