#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>

class LocalUser
{
public:
    static LocalUser & getLocalUser();
    const std::string getUsername() const;
    const std::string getPassword() const;
    void setPassword(const std::string& password);

private:
    LocalUser();
    ~LocalUser();
    LocalUser(const LocalUser &) = delete;
    LocalUser& operator=(const LocalUser &) = delete;

    const std::string username_;
    std::string password_;

    Logger log_ {LogSpace::UserService};
};
