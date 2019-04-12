#pragma once

#include <string>

#include "NcursesPrintOperationWrapper.hpp"

namespace
{
static constexpr auto hello = "Hello ";
static constexpr auto enterPassword = "Enter the password : ";
static constexpr auto informationToDisplayInMainWindow = "You are currently logged as ";
static constexpr auto informationToDisplayDuringSignIn = ". If you want use messenger, you need to log in.";
static constexpr auto informationToDisplayDuringRegistration =
        ". You are using messenger first time. You need create account. Enter your password twice.";

}//namespace


class NcursesPrintToMainWindowOperationWrapper : public NcursesPrintOperationWrapper
{
public:
    void printInformationIntoMainWindow(const std::string&) const override;
    void printMainWindow() const override;
    void printRegistrationWindow() const override;
    void printSignInWindow() const override;
private:
    void printBasesInformationIntoMainWindow(const std::initializer_list<const char*> &&) const;
    void printInformationAboutEnteringPassword() const;
};
