#pragma once
#include <memory>
#include <string>
#include <queue>
#include <thread>

#include <FileHandling.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class Sender
{
public:
    Sender(const std::string& pathToChatFile, int chatFlag);
    ~Sender();

    bool sendMessage();

private:
    std::unique_ptr<std::string> getMessageFromStdin() const;
    std::unique_ptr<std::string> getActualDateTime() const;
    bool prepearMessageToSend(const std::string& rowMessage);
    bool setNewMessageFlag(const std::string& folderName) const;
    void sendMessageFromWaitingRoom();

    std::thread sendMessage_ ;
    //bez tego unique ?
    std::queue<std::unique_ptr<std::string>> messageWaitngRoom_;
    bool isMessageWaitngRoomEmpty_ = false;
    std::string pathToChatFile_;
    int chatFlag_;

    Logger log {LogSpace::ChatFile};
};
