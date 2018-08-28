#pragma once
// nie dodane do kompilowania

class ConversationControl //: public ChatControl
{
public:
    void conversation();
    void conversationEpilog();

private:
    void getMessage();
    void reciveMessage();
    void sendMessage();
    void stopThreads();
}
