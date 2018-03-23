#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include <ClasslessLogger.hpp>
#include <LogSpace.hpp>
#include <FileHandling.hpp>

namespace
{
    std::unique_ptr<std::fstream> openFileToRead(const std::string& pathToFile)
    {
        fileLog("FileInterface::openFileToRead started", LogSpace::FileHandling);
        if (!FileInterface::Managment::isFileExist(pathToFile))
        {
            std::string logInfo = "FileInterface::openFileToRead ERROR: " + pathToFile + " does not exist";
            fileLog(logInfo.c_str(), LogSpace::FileHandling);
            return nullptr;
        }

        std::string folderName = *FileInterface::Accesor::getFolderName(pathToFile);

        if (!FileInterface::Managment::isFileExist(folderName + "/GUARD"))
        {
            FileInterface::Managment::createFile(folderName + "/GUARD");
        }
        else
        {
            std::string logInfo = "FileInterface::openFileToRead ERROR: cannot get access to" + pathToFile;
            fileLog(logInfo.c_str(), LogSpace::FileHandling);
            return nullptr;
        }

        std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();
        fileToOpen->open(pathToFile, std::ios::in);

        if (fileToOpen->is_open())
        {
            return fileToOpen;
        }
        else
        {
            fileLog("FileInterface::openFileToRead ERROR: is_open() failed", LogSpace::FileHandling);
            return nullptr;
        }
    }

    std::unique_ptr<std::fstream> openFileToWrite(const std::string& pathToFile)
    {
        fileLog("FileInterface::openFileToWrite started", LogSpace::FileHandling);
        if (!FileInterface::Managment::isFileExist(pathToFile))
        {
            std::string logInfo = "FileInterface::openFileToWrite ERROR: " + pathToFile + " does not exist";
            fileLog(logInfo.c_str(), LogSpace::FileHandling);
            return nullptr;
        }

        std::string folderName = *FileInterface::Accesor::getFolderName(pathToFile);

        if (!FileInterface::Managment::isFileExist(folderName + "/GUARD"))
        {
            FileInterface::Managment::createFile(folderName + "/GUARD");
        }
        else
        {
            std::string logInfo = "FileInterface::openFileToWrite ERROR: cannot get access to" + pathToFile;
            fileLog(logInfo.c_str(), LogSpace::FileHandling);
            return nullptr;
        }

        std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();
        fileToOpen->open(pathToFile, std::ios::out | std::ios::app);

        if (fileToOpen->is_open())
        {
            return fileToOpen;
        }
        else
        {
            fileLog("FileInterface::openFileToWrite ERROR: is_open() failed", LogSpace::FileHandling);
            return nullptr;
        }
    }
}

bool FileInterface::Modification::addRow(const std::string& pathToFile, const std::string& text)
{
    fileLog("FileInterface::Modification::addRow started", LogSpace::FileHandling);
    if (std::unique_ptr<std::fstream> file = openFileToWrite(pathToFile))
    {
        *file << text;
        *file << '\n';
        std::string folderName = *Accesor::getFolderName(pathToFile);
        Managment::removeFile(folderName + "/GUARD");
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
    system(systemCommand.c_str());

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
        Managment::removeFile(folderName + "/GUARD");
        return nullptr;
    }

    Managment::removeFile(folderName + "/GUARD");

    return fileContent;
}

std::unique_ptr<std::vector<std::string>> FileInterface::Accesor::getFilenamesFromFolder(const std::string& pathToDir)
{
    std::string logInfo = "FileInterface::Accesor::getFilenamesFromFolder from " + pathToDir;
    fileLog(logInfo.c_str(), LogSpace::FileHandling);
    std::string command = "ls " + pathToDir;
    std::string commandOutput = ConsolControl::getStdoutFromCommand(command);

    std::unique_ptr<std::vector<std::string>> filesNames = std::make_unique<std::vector< std::string>>();
    std::string fileName;

    const int lastWhitespaceCharacterASCII = 32;
    for (auto& x : commandOutput)
    {
        if (lastWhitespaceCharacterASCII < x )
        {
            fileName += x;
        }
        else
        {
            filesNames->push_back(fileName);
            fileName.clear();
        }
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
    fileLog("FileInterface::Accesor::getRowField  started", LogSpace::FileHandling);
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

bool FileInterface::Managment::isFileExist(const std::string& pathToFile)
{
    std::string logInfo = "FileInterface::Managment::isFileExist " + pathToFile;
    fileLog(logInfo.c_str(), LogSpace::FileHandling);
    std::ifstream file(pathToFile);
    return file.good();
}

bool FileInterface::Managment::removeFile(const std::string& pathToFile)
{
    std::string logInfo = "FileInterface::Managment::removeFile " + pathToFile;
    fileLog(logInfo.c_str(), LogSpace::FileHandling);
    const char * c = pathToFile.c_str();
    return ! std::remove(c); // 0 when success
}



std::unique_ptr<std::string> FileInterface::Modification::removeRowField(const std::string& row, const int fieldNumber)
{
    fileLog("FileInterface::Modification::removeRowField  started", LogSpace::FileHandling);
    int actualFieldNumber = -1;
    std::unique_ptr<std::string> rowWithoutRemovedField = std::make_unique<std::string>();

    for (auto &x : row)
    {
        if ('[' == x)
        {
            ++actualFieldNumber;
        }

        if (actualFieldNumber != fieldNumber)
        {
            rowWithoutRemovedField -> push_back(x);
        }
    }

    return rowWithoutRemovedField;
}


bool FileInterface::Modification::removeRow(const std::string& pathToFile, const std::string& pattern)
{
    fileLog("FileInterface::Modification::removeRow  started", LogSpace::FileHandling);
    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (Managment::isFileExist(folderName + "/GUARD"))
    {
        return false;
    }

    Managment::createFile(folderName + "/GUARD");

    std::string command = "sed -i -e '/" + pattern + "/d' " + pathToFile;
    std::system(command.c_str());

    bool isGuardRemoved = Managment::removeFile(folderName + "/GUARD");

    return isGuardRemoved;
}


bool FileInterface::Modification::updateRow(const std::string & pathToFile, const std::string & newRow, const std::string & where)
{
    fileLog("FileInterface::Modification::updateRow  started", LogSpace::FileHandling);
    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (Managment::isFileExist(folderName + "/GUARD"))
    {
        fileLog("FileInterface::Modification::updateRow ERROR: File does not exist", LogSpace::FileHandling);
        return false;
    }

    Managment::createFile(folderName + "/GUARD");

    std::string command = "sed -i -e 's/.*" + where + ".*/" + newRow + "/g' " + pathToFile;
    //TODO mwozniak ^zeby podmienialo tylko pierwsze znalezione wystapienie
    std::system(command.c_str());

    bool isGuardRemoved = Managment::removeFile(folderName + "/GUARD");

    return isGuardRemoved;
}


std::unique_ptr<std::string> FileInterface::Modification::updateRowField(const std::string& row, const std::string& newField, const int fieldNumber)
{
    fileLog("FileInterface::Modification::updateRowField  started", LogSpace::FileHandling);
    int actualFieldNumber = -1;
    bool flag = false;
    std::unique_ptr< std::string> rowToUpdate = std::make_unique<std::string>();
    //TODO mwozniak jest to bardzo brzydkie, poprawic ! Ale dziala ;p
    for (auto &x : row)
    {
        if ('[' == x)
        {
            ++actualFieldNumber;
        }

        if (actualFieldNumber != fieldNumber)
        {
            rowToUpdate -> push_back(x);
        }
        else
        {
            if (true == flag)
                continue;

            rowToUpdate -> push_back('[');

            for (auto& y : newField)
            {
                rowToUpdate -> push_back(y);
            }

            flag = true;
            rowToUpdate -> push_back(']');
        }
    }
    return rowToUpdate;
}




/** TO NIZEJ GDIZE INDZIEJ*/

std::string ConsolControl::getStdoutFromCommand(std::string cmd)
{
    fileLog("ConsolControl::getStdoutFromCommand  started", LogSpace::FileHandling);
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

    return data;
}
