# TEST FILES WITH GTEST/GMOCK UNIT TESTS
set(TEST_FILES ${TEST_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ChatRequestTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ChatRequestTestCore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ChatFabricTest.cpp PARENT_SCOPE)

#SOURCES FILES WHICH ARE NEEDED TO COMPILE TESTS
set(TEST_SOURCES ${TEST_SOURCES}
    ${MODULE_FileHandling}/SHA1.cpp
    ${MODULE_UserService}/User.cpp
    ${MODULE_UserService}/LocalUser.cpp
    ${MODULE_UserService}/SignIn.cpp
    ${MODULE_UserService}/SignOut.cpp
    ${MODULE_UserService}/RegisterUser.cpp
    ${MODULE_ChatControl}/Sender.cpp
    ${MODULE_ChatControl}/Receiver.cpp
    ${MODULE_ChatControl}/ChatControl.cpp
    ${MODULE_ChatStarter}/ChatFabric.cpp
    ${MODULE_ChatStarter}/ChatRequest.cpp PARENT_SCOPE)
