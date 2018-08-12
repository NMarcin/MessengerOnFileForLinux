#pragma once
#include <stack>
#include <queue>
#include <string>
/*
- pobieramy cały plik
- blokujemy dostęp do pliku
-

- pobieramy od końca pliku linijki które mają odpowiednią flagę na początku
- uzywamy do tego stosu, bo potem w odwrotnej kolejnosci bedziemy chcieli wrzucac do kolejki
- nastepnie z tego stosu zabieram po linijce i oprawiamy ja i zwracamy w innej funkcji
- kolejna funkcja wrzuca oprawiona linijke do naszej kolejki do wyswietlania
*/

class Receiver
{
public:
    Receiver(std::string chatFileWithPath, std::string mineMessageUserFlag);      // chatFileWithPath -> do konstruktora
    ~Receiver();

    bool readMessagesToStack();
    std::string returnTheOldestMessage();

private:
    bool updateSeenFlags();
    bool endOfMessageToRead(std::string message, std::string messageFlag);
    void pushPurgeMessageOnStack(std::string rawMessageToPush);
    std::string purgeMessageFromRaw(std::string rawMessage);

    const std::string chatFileWithPath_;
    std::stack<std::string> purgeMessagesStack_;
    std::string mineMessageUserFlag_;
};
