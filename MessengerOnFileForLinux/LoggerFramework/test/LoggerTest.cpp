#include <gtest/gtest.h>
#include <Logger.hpp>
#include <LogSpace.hpp>
#include <ClasslessLogger.hpp>

#include <FileHandling.hpp>
#include <fstream>



TEST(LoggerFrameworkTest, logFileCreation)
{
    EXPECT_FALSE(FileInterface::Managment::isFileExist("Logger_default.txt"));
    Logger log(LogSpace::Logger);
    log.info("Test log");
    EXPECT_TRUE(FileInterface::Managment::isFileExist("Logger_default.txt"));

    FileInterface::Managment::removeFile("Logger_default.txt");
}

TEST(LoggerFrameworkTest, logFileCreationWithoutClass)
{
    EXPECT_FALSE(FileInterface::Managment::isFileExist("Logger_default.txt"));
    fileLog("Test log", LogSpace::Logger);
    EXPECT_TRUE(FileInterface::Managment::isFileExist("Logger_default.txt"));

    FileInterface::Managment::removeFile("Logger_default.txt");
}

TEST(LoggerFrameworkTest, writingToLogFile)
{
    Logger log(LogSpace::Logger);
    log.info("Test log");
    std::ifstream logFile("Logger_default.txt", std::ifstream::ate);
    int fileSize = logFile.tellg();

    EXPECT_TRUE(fileSize);

    FileInterface::Managment::removeFile("Logger_default.txt");
}

TEST(LoggerFrameworkTest, writingToLogFileWithoutClass)
{
    fileLog("Test log", LogSpace::Logger);
    std::ifstream logFile("Logger_default.txt", std::ifstream::ate);
    int fileSize = logFile.tellg();

    EXPECT_TRUE(fileSize);

    FileInterface::Managment::removeFile("Logger_default.txt");
}

TEST(LoggerFrameworkTest, isLogCorrectlyAdded)
{
    Logger log(LogSpace::Logger);
    std::string logInfo = "Test log";
    log.info(logInfo);
    std::string expectedLog = "Logger \t " + logInfo;

    std::fstream logFile("Logger_default.txt", std::ios::in);
    std::string logInFile;
    getline(logFile, logInFile);

    const int DateTimeSize = 21;
    logInFile.erase(logInFile.begin(), logInFile.begin() + DateTimeSize);

    EXPECT_EQ(expectedLog, logInFile);

    FileInterface::Managment::removeFile("Logger_default.txt");
}

TEST(LoggerFrameworkTest, isLogCorrectlyAddedWithoutClass)
{
    std::string logInfo = "Test log";
    fileLog(logInfo.c_str(), LogSpace::Logger);
    std::string expectedLog = "Logger \t " + logInfo;

    std::fstream logFile("Logger_default.txt", std::ios::in);
    std::string logInFile;
    getline(logFile, logInFile);

    const int DateTimeSize = 21;
    logInFile.erase(logInFile.begin(), logInFile.begin() + DateTimeSize);

    EXPECT_EQ(expectedLog, logInFile);

    FileInterface::Managment::removeFile("Logger_default.txt");
}

TEST(LoggerFrameworkTest, isLogNotOverwritten)
{
    Logger log(LogSpace::Logger);
    log.info("Test log");
    std::ifstream logFile("Logger_default.txt", std::ifstream::ate);
    int fileSize = logFile.tellg();
    logFile.close();

    log.info("Test log");
    std::ifstream logFileAgain("Logger_default.txt", std::ifstream::ate);
    int newFileSize = logFileAgain.tellg();


    EXPECT_TRUE(newFileSize > fileSize);

    FileInterface::Managment::removeFile("Logger_default.txt");
}
