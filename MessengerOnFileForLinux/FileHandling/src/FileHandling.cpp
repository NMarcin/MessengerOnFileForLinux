#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ClasslessLogger.hpp>
#include <LogSpace.hpp>
#include <FileHandling.hpp>

bool FileInterface::lockFolder(const std::string& pathToFolder)
{
    if (!FileInterface::Managment::isFileExist(pathToFolder + "/GUARD"))
    {
        std::string systemCommand = "touch " + pathToFolder + "/GUARD";
        system(systemCommand.c_str());
        return FileInterface::Managment::isFileExist(pathToFolder + "/GUARD");
    }
    return false;
}

bool FileInterface::unlockFolder(const std::string& pathToFolder)
{
    std::string command = "rm -r " + pathToFolder + "/GUARD";
    system(command.c_str());
    return ! FileInterface::Managment::isFileExist(pathToFolder + "/GUARD");
}

namespace
{
enum class FileMode
{
    toWrite,
    toRead
};

bool createGuardian(const std::string& pathToFolder)
{
    std::string systemCommand = "touch " + pathToFolder + "/GUARD";
    system(systemCommand.c_str());
    return FileInterface::Managment::isFileExist(pathToFolder + "/GUARD");
}

bool removeGuardian(const std::string& pathToFolder)
{
    std::string command = "rm -r " + pathToFolder + "/GUARD";
    system(command.c_str());
    return ! FileInterface::Managment::isFileExist(pathToFolder + "/GUARD");
}

bool isGuardianExist(const std::string& pathToFolder)
{
    return FileInterface::Managment::isFileExist(pathToFolder + "/GUARD");
}

std::unique_ptr<std::fstream> openFile(const std::string& pathToFile, FileMode mode)
{
    fileLog("FileInterface::openFile started in FileMode = " + static_cast<int>(mode), LogSpace::FileHandling);
    if (!FileInterface::Managment::isFileExist(pathToFile))
    {
        std::string logInfo = "FileInterface::openFile ERROR: " + pathToFile + " does not exist";
        fileLog(logInfo.c_str(), LogSpace::FileHandling);
        return nullptr;
    }

    std::string folderName = *FileInterface::Accesor::getFolderName(pathToFile);

    bool accesToFile = false;

    while(!accesToFile)
    {
        if (!isGuardianExist(folderName))
        {
            createGuardian(folderName);
            accesToFile = true;
        }
    }

    std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();

    if (FileMode::toRead == mode)
    {
        fileToOpen->open(pathToFile, std::ios::in);
    }
    else if (FileMode::toWrite == mode)
    {
        fileToOpen->open(pathToFile, std::ios::out | std::ios::app);
    }

    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        fileLog("FileInterface::openFile ERROR: is_open() failed", LogSpace::FileHandling);
        return nullptr;
    }
}

std::unique_ptr<std::fstream> openFileToWrite(const std::string& pathToFile)
{
    return openFile(pathToFile, FileMode::toWrite);
}

std::unique_ptr<std::fstream> openFileToRead(const std::string& pathToFile)
{
    return openFile(pathToFile, FileMode::toRead);
}


}


bool FileInterface::Modification::addRow(const std::string& pathToFile, const std::string& text)
{
    fileLog(("FileInterface::Modification::addRow Add row to " + pathToFile).c_str(), LogSpace::FileHandling);
    if (std::unique_ptr<std::fstream> file = openFileToWrite(pathToFile))
    {
        *file << text;
        *file << '\n';
        std::string folderName = *Accesor::getFolderName(pathToFile);
        removeGuardian(folderName);
        return true;
    }
    else
    {
        fileLog("FileInterface::Modification::addRow ERROR: Cannot get file acces", LogSpace::FileHandling);
        return false;
    }
}


bool FileInterface::Managment::createFile(const std::string& pathToFile)
{
    std::string logInfo = "FileInterface::Managment::createFile " + pathToFile;
    fileLog(logInfo.c_str(), LogSpace::FileHandling);
    std::string systemCommand = "touch " + pathToFile;
    std::string systemCommand2 = "chmod 777 " + pathToFile;
    system(systemCommand.c_str());
    system(systemCommand2.c_str());

    if (!isFileExist(pathToFile))
    {
        std::string logInfo = "FileInterface::Managment::createFile started ERROR: " + pathToFile + "was not create";
        fileLog(logInfo.c_str(), LogSpace::FileHandling);
        return false;
    }
}

std::unique_ptr<std::vector<std::string>> FileInterface::Accesor::getFileContent(const std::string& pathToFile)
{
    std::string logInfo = "FileInterface::Accesor::getFileContent " + pathToFile;
    fileLog(logInfo.c_str(), LogSpace::FileHandling);
    std::unique_ptr<std::vector<std::string>> fileContent = std::make_unique<std::vector<std::string>>();
    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (std::unique_ptr<std::fstream> file = openFileToRead(pathToFile))
    {
        while (!file->eof())
        {
            std::string row;
            std::getline(*file, row);
            fileContent -> push_back(row);
        }
    }
    else
    {
        std::string logInfo = "FileInterface::Accesor::getFileContent ERROR: Cannot get acces to "  + pathToFile;
        fileLog(logInfo.c_str(), LogSpace::FileHandling);
        removeGuardian(folderName);
        return nullptr;
    }

    removeGuardian(folderName);

    return fileContent;
}

std::unique_ptr<std::vector<std::string>> FileInterface::Accesor::getFilenamesFromFolder(const std::string& pathToDir)
{
    std::string command = "ls " + pathToDir;
    std::string commandOutput = ConsolControl::getStdoutFromCommand(command);

    std::unique_ptr<std::vector<std::string>> filesNames = std::make_unique<std::vector< std::string>>();
    std::string fileName;

    auto it = commandOutput.begin();
    for (auto& x : commandOutput)
    {
        if (commandOutput.end() - 1 == it)
        {
            fileName += x;
            filesNames->push_back(fileName);
        }
        else if ('\n' != x)
        {
            fileName += x;
        }
        else
        {
            filesNames->push_back(fileName);
            fileName.clear();
        }
        it++;
    }

    return filesNames;
}

std::unique_ptr<std::string> FileInterface::Accesor::getFolderName(const std::string& pathToFile)
{
    std::string logInfo = "FileInterface::Accesor::getFolderName  from " + pathToFile;
    fileLog(logInfo.c_str(), LogSpace::FileHandling);
    auto it = pathToFile.end();

    while ('/' != *it)
    {
        --it;
    }

    std::unique_ptr<std::string> folderName = std::make_unique<std::string>(pathToFile.begin(), it);

    return folderName;
}


std::unique_ptr<std::string> FileInterface::Accesor::getRowField(const std::string& field, const int fieldNumber)
{
    fileLog("FileInterface::Accesor::getRowField started from ", LogSpace::FileHandling);
    int actualFieldNumber = -1;
    std::unique_ptr<std::string> fieldToDownload = std::make_unique<std::string>();

    std::string::iterator it;
    for (auto& x : field)
    {
        if ('[' == x)
        {
            ++actualFieldNumber;
        }
        else if (actualFieldNumber == fieldNumber && ']' != x)
        {
            *fieldToDownload += x;
        }
    }
    return fieldToDownload;
}

std::unique_ptr<std::string> FileInterface::Accesor::getRow(const std::string& pathToFile, const std::string& pattern)
{
    std::string folderName = *Accesor::getFolderName(pathToFile);
    if (isGuardianExist(folderName))
    {
        return nullptr;
    }

    createGuardian(folderName);
    std::string command = "grep '" + pattern + "' " +  pathToFile;
    std::string commandOutput = ConsolControl::getStdoutFromCommand(command);
    removeGuardian(folderName);
    if (commandOutput.empty())
    {
        return nullptr;
    }

    return std::make_unique<std::string>(commandOutput);
}

bool FileInterface::Managment::isFileExist(const std::string& pathToFile)
{
    bool isFileExist = (-1 != access(pathToFile.c_str(), F_OK ));
    return isFileExist;
}

bool FileInterface::Managment::removeFile(const std::string& pathToFile)
{
    std::string command = "rm -r " + pathToFile;
    system(command.c_str());

    return ! isFileExist(pathToFile);
}

bool FileInterface::Modification::removeRow(const std::string& pathToFile, const std::string& pattern)
{
    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (isGuardianExist(folderName))
    {
        return false;
    }

    createGuardian(folderName);

    std::string command = "sed -i -e '/" + pattern + "/d' " + pathToFile;
    std::system(command.c_str());

    bool isGuardRemoved = removeGuardian(folderName);

    return isGuardRemoved;
}

bool FileInterface::Modification::updateRow(const std::string & pathToFile, const std::string & newRow, const std::string & where)
{
    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (isGuardianExist(folderName))
    {
        fileLog("FileInterface::Modification::updateRow ERROR: File does not exist", LogSpace::FileHandling);
        return false;
    }

    createGuardian(folderName);

    std::string command = "sed -i -e 's/.*" + where + ".*/" + newRow + "/g' " + pathToFile;
    //TODO mwozniak ^zeby podmienialo tylko pierwsze znalezione wystapienie
    std::system(command.c_str());

    bool isGuardRemoved = removeGuardian(folderName);

    return isGuardRemoved;
}

bool FileInterface::Modification::updateFlagsInFile(const std::string& pathToFile, const std::string& flagToReplace, const std::string& newFlag)
{
    int actualFieldNumber = -1;
    bool flag = false;

    std::string folderName = *Accesor::getFolderName(pathToFile);
    if (isGuardianExist(folderName))
    {
        return false;
    }

    createGuardian(folderName);

    std::string command = "sed -i -e '/\[" + flagToReplace + "]/{s/" + flagToReplace + "/" + newFlag + "/}' " + pathToFile;
    std::system(command.c_str());

    removeGuardian(folderName);
    return true;
}

bool FileInterface::Modification::updateRowField(const std::string& pathToFile, const std::string& where, const std::string& newField, const int fieldNumber = 0)
{
    int actualFieldNumber = -1;

    std::string folderName = *Accesor::getFolderName(pathToFile);
    if (isGuardianExist(folderName))
    {
        return false;
    }

    createGuardian(folderName);

    std::string command = "grep '" + where + "' " + pathToFile;
    std::string row = ConsolControl::getStdoutFromCommand(command.c_str());

    std::string rowToUpdate;
    auto it = row.begin();
    for (auto& x : row)
    {
        if ('[' == x)
        {
            ++actualFieldNumber;
        }

        else if (actualFieldNumber == fieldNumber)
        {
            rowToUpdate = std::string(row.begin(), it) + newField;
            it = it + newField.size();
            rowToUpdate += "]" + std::string(it, row.end());
            break;
        }
        it++;
    }

    removeGuardian(folderName);
    command = "sed -i -e 's/.*" + where + ".*/" + rowToUpdate + "/g' " + pathToFile;
    //cos w stylu sed -i -e '0,/where/s..............
    //TODO mwozniak ^zeby podmienialo tylko pierwsze znalezione wystapienie
    std::system(command.c_str());

    return true;
}

/** TO NIZEJ GDIZE INDZIEJ*/

std::string ConsolControl::getStdoutFromCommand(std::string cmd)
{
    std::string data;
    FILE * stream;
    const int max_buffer = 1024;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
        {
            if (fgets(buffer, max_buffer, stream) != NULL)
            {
                data.append(buffer);
            }
        }
        pclose(stream);
    }
    if (data.size())
        data.pop_back(); //usuwanie smieci konca linii
    return data;
}
