#pragma once
#include <memory>

#include <Sender.hpp>
#include <Reciver.hpp>

enum class UserType
{
    sender,
    reciver
};

class ChatControler
{
public:
    ChatControler();
    ~ChatControler();

private:

    std::unique_ptr<Sender> sender_;
    std::unique_ptr<Reciver> reciver_;
    std::string folderName;
    std::string fileName;

};

