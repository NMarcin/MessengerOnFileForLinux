#include <iostream>

#include <LocalUser.hpp>
#include <FileHandling.hpp>

LocalUser::LocalUser()
    : username_(getenv("USER"))
{
    log_.function("LoclaUser C-TOR");
}

LocalUser::~LocalUser()
{
    log_.function("LoclaUser D-TOR");
}

LocalUser & LocalUser::getLocalUser()
{
    static LocalUser localUser;
    return localUser;
}

const std::string LocalUser::getUsername() const
{
    log_.function("LocalUser::getUsername() started");
    return username_;
}

const std::string LocalUser::getPassword() const
{
    log_.function("User::getPassword() started");
    return password_;
}

void LocalUser::setPassword(const std::string& password)
{
    log_.function("User::setPassword() started");
    password_ = password;
}
