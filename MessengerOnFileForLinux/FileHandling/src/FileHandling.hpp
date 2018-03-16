#pragma once
#include<memory>
#include<vector>
#include<string>
#include<fstream>
/*
namespace FileInterface
{
    bool createFile(const std::string& fileName, const std::string& pathToFile = "");
    bool removeFile(const std::string& fileName, const std::string& pathToFile = "");

    namespace Modification
    {
        bool addRow(const  std::string& fileName, const std::string& text, const std::string& pathToFile = "");
        bool removeRow(const std::string& fileName, const std::string& pattern, const std::string& pathToFile = "");
        std::unique_ptr<std::string> removeRowField(const std::string& row, const int fieldNumber);
        bool removeRow(const std::string& fileName, const std::string& pattern, const std::string& pathToFile = "");
        bool updateRow(const std::string& fileName, const std::string& newRow, const std::string& where, const std::string& pathToFile = "");
        std::unique_ptr<std::string> updateRowField(const std::string& row, const std::string& newField, const int fieldNumber);
    }

    namespace Get  // JAKIS LEPSZY POMYSL ???????????
    {
        std::unique_ptr<std::vector<std::string>> getFilenamesFromFolder(const std::string& pathToDir = "");
        std::unique_ptr<std::string> getRowField(const std::string& field, const int fieldNumber);
        std::unique_ptr<std::vector<std::string>> getFileContent(const std::string& fileName, const std::string& pathToFile = "");
    }

    namespace Managment
    {
        bool closeFile(const std::string& fileToClose, const std::string& pathToFile = "");
        bool isGuardExist(const std::string& fileName, const std::string& pathToFile = "");
        bool isFileExist(const std::string& fileName, const std::string& pathToFile = "");
        std::unique_ptr<std::fstream> openFileToRead(const std::string& fileName, const std::string& pathToFile = "");
        std::unique_ptr<std::fstream> openFileToSave(const std::string& fileName, const std::string& pathToFile = "");
    }

}
*/
namespace FileInterface
{
    bool addRow(const  std::string& fileName, const std::string& text, const std::string& pathToFile = "");
    bool closeFile(const std::string& fileToClose, const std::string& pathToFile = "");
    bool createFile(const std::string& fileName, const std::string& pathToFile = "");
    bool getFileAccess(const std::string& fileName, const std::string& pathToFile = "");
    std::unique_ptr<std::vector<std::string>> getFilenamesFromFolder(const std::string& pathToDir = "");
    std::unique_ptr<std::string> getRowField(const std::string& field, const int fieldNumber);
    bool isFileExist(const std::string& fileName, const std::string& pathToFile = "");
    std::unique_ptr<std::fstream> openFileToRead(const std::string& fileName, const std::string& pathToFile = "");
    std::unique_ptr<std::fstream> openFileToSave(const std::string& fileName, const std::string& pathToFile = "");
    std::unique_ptr<std::string> removeRowField(const std::string& row, const int fieldNumber);
    std::unique_ptr<std::vector<std::string>> getFileContent(const std::string& fileName, const std::string& pathToFile = "");
    bool removeRow(const std::string& fileName, const std::string& pattern, const std::string& pathToFile = "");
    bool removeFile(const std::string& fileName, const std::string& pathToFile = "");
    bool updateRow(const std::string& fileName, const std::string& newRow, const std::string& where, const std::string& pathToFile = "");
    std::unique_ptr<std::string> updateRowField(const std::string& row, const std::string& newField, const int fieldNumber);
    bool isGuardExist(const std::string& fileName, const std::string& pathToFile = "");
}

/** wrzucic to gdzie indzie*/
//TODO mwozniak mnurzyn jaka nazwa ?
namespace System
{
std::string getActualDateTime();//DONE
std::string getStdoutFromCommand(std::string cmd);
}



