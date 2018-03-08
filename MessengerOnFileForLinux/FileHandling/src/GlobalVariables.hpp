#pragma once
#include <string>

static constexpr char registeredFile[] = "registered.txt";
static constexpr char loggedFile[] = "logged.txt";

static constexpr char userActiveStatus = '0';
static constexpr char userBusyStatus = '1';

static constexpr int usernameFieldInLoggedFile = 0;
static constexpr int usernameFieldInRegisteredFile = 0;
static constexpr int passwordFieldInRegisteredFile = 1;

enum class FileFlagType
{
    guardian,
    newFlag
};



