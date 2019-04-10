#include <iostream>

#include <LocalUser.hpp>
#include <FileHandling.hpp>

LocalUser::LocalUser()
    : _username(getenv("USER"))
{
    _log.function("LoclaUser C-TOR");
}

LocalUser& LocalUser::getLocalUser()
{
    static LocalUser localUser;
    return localUser;
}

const std::string LocalUser::getUsername() const
{
    _log.function("LocalUser::getUsername() started");
    return _username;
}
