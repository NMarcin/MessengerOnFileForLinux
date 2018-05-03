#pragma once
#include <memory>
#include <string>

#include <FileHandling.hpp>     // TODO mwozniak to nie powinno byc tutaj, a w .cpp, nie korzystasz z tego w tym pliku
#include <Logger.hpp>
#include <LogSpace.hpp>
/**
  USUNE TO PO REVIEW
  W konstruktorze dostajemy sciezke do chatFile i odpowiednia flage (1 albo 2).
  getMessageToSend() pobiera z konsoli wiadomosc, opakowuje ja i zwraca.
  sendMessage() wysyla wiadomosc do pliku i ustawia flage NEW
 */
class Sender
{
public:
    Sender(const std::string& pathToChatFile, int chatFlag);
    ~Sender();

    std::unique_ptr<std::string> getMessageToSend() const;
    bool sendMessage(const std::string& message) const;

private:
    std::unique_ptr<std::string> getMessageFromStdin() const;
    std::unique_ptr<std::string> getActualDateTime() const;
    std::unique_ptr<std::string> prepareMessageToSend(const std::string& rowMessage) const;
    bool setNewMessageFlag() const;

    std::string chatFilenameWithPath_;
    int chatFlag_;

    Logger log {LogSpace::ChatFile};
};
