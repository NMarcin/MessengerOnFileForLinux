#pragma once
#include <LocalUser.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

#include <signal.h> //to wszystko ponizej potrzebne do initu dzialania sygnalu
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <csignal>

class SignOut
{
public:
    bool signOutUser() const;

    SignOut();
    ~SignOut();

private:
    bool removeUserDataFromLoggedFile() const;

    Logger log {LogSpace::UserService};
};

