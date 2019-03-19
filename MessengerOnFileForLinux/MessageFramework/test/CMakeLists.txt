# TEST FILES WITH GTEST/GMOCK UNIT TESTS
set(TEST_FILES ${TEST_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/StringSumTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PurgeMessageTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PurgeMessageTestCore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MessageTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MessageTestCore.cpp PARENT_SCOPE)

#SOURCES FILES WHICH ARE NEEDED TO COMPILE TESTS
set(TEST_SOURCES ${TEST_SOURCES}
    ${MODULE_Common}/SHA1.cpp
    ${MODULE_Common}/SignalHandling.cpp
    ${MODULE_Common}/TimeManagment.cpp
    ${MODULE_UserService}/User.cpp
    ${MODULE_UserService}/LocalUser.cpp
    ${MODULE_UserService}/SignIn.cpp
    ${MODULE_UserService}/SignOut.cpp
    ${MODULE_UserService}/RegisterUser.cpp
    ${MODULE_ChatControl}/Sender.cpp
    ${MODULE_DisplayChat}/ConsoleWindow.cpp
    ${MODULE_ChatControl}/Receiver.cpp
    ${MODULE_ChatControl}/ConversationControl.cpp
    ${MODULE_ChatControl}/UserInactivityDetector.cpp
    ${MODULE_ChatStarter}/ChatFabric.cpp
    ${MODULE_TerminalFunctionality}/TerminalFunctionality.cpp
    ${MODULE_TerminalFunctionality}/TerminalCommand.cpp
    ${MODULE_ChatControl}/TerminalControl.cpp
    ${MODULE_TerminalFunctionality}/HistoryDowloander.cpp
    ${MODULE_TerminalFunctionality}/LoggingOut.cpp
    ${MODULE_ChatStarter}/ChatRequest.cpp
    ${MODULE_MessageFramework}/Message.cpp
    ${MODULE_MessageFramework}/PurgeMessage.cpp
    ${MODULE_MessageFramework}/StringSum.cpp
    ${MODULE_TerminalFunctionality}/InviteSender.cpp
    ${MODULE_TerminalFunctionality}/InviteReceiver.cpp
    ${MODULE_TerminalFunctionality}/EndConversation.cpp
    ${MODULE_DisplayChat}/ChatWindow.cpp PARENT_SCOPE)
