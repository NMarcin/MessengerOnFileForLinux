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

class Reciver
{
public:
    Reciver();      // chatFileWithPath -> do konstruktora
    ~Reciver();

    bool readMessages();

private:
    bool getRawMessagesFromFile(std::string chatFileWithPath);                                          // pobiera wszystkie linijki NEW z pliku
    std::string getMessageFromStack();                                                                  // pobiera wiadomość ze stosu i ją zwraca
    std::string purgeMessageFromRaw(std::string rawMessage);                                                   // otrzymanego stringa oczyszcza na stringa, ktory zostanie wyświetlony na odpowiednim ekranie
    bool addMessageToQueue(std::queue<std::string> messagesToShowOnScreen, std::string purgeMessage);   // otrzymanego stringa wrzuca do kolejki, na którą ma wskaźnik, tej z Chat Controla

    const std::string chatFileWithPath;
    std::stack<std::string> purgeMessagesStack;
    int mineMessageUserFlag;
};
