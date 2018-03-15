#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include <FileHandling.hpp>
#include <FileGuardian.hpp>

bool FileInterface::addRow(const std::string& fileName, const std::string& text, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    if (std::unique_ptr<std::fstream> file = openFileToSave(fileLocation))
    {
        *file << text;
        *file << '\n';
        closeFile(fileLocation);
        return true;
    }
    else
    {
        return false;
        //TODO mwozniak error
        //skad wiemy czy plik nieistenije czy jest guearian?
    }
}


bool FileInterface::closeFile(const std::string& fileName, const std::string& pathToFile)
{    
    FileFlag::removeFileFlag(FileFlagType::guardian, pathToFile, fileName);
}

bool FileInterface::createFile(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    std::string systemCommand = "touch " + fileLocation;
    system(systemCommand.c_str());

    return isFileExists(fileName, pathToFile);
}

bool FileInterface::getFileAccess(const std::string& fileName, const std::string& pathToFile)
{
    return !FileFlag::isFlagExist(FileFlagType::guardian, pathToFile, fileName);
}

std::unique_ptr<std::vector<std::string>> FileInterface::getFilesNames(const std::string& pathToDir)
{
    std::string command = "ls " + pathToDir;
    std::string commandOutput = System::getStdoutFromCommand(command);

    std::unique_ptr<std::vector<std::string>> filesNames = std::make_unique<std::vector< std::string>>();
    std::string fileName;

    for (auto& x : commandOutput)
    {
        if (20 < x ) //ASCI bo byl problem z ' '
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

std::unique_ptr<std::string> FileInterface::getRowField(const std::string& field, const int fieldNumber)
{
    int actualFieldNumber = -1;
    std::unique_ptr<std::string> fieldToDownload = std::make_unique<std::string>();

    for (auto& x : field)
    {
        if ('[' == x)
        {
            ++actualFieldNumber;
        }
        else if (actualFieldNumber == fieldNumber && ']' != x)
        {
            fieldToDownload -> push_back(x);
        }
    }
    return fieldToDownload;
}

bool FileInterface::isFileExists(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    std::ifstream file(fileLocation);
    return file.good();
}

std::unique_ptr<std::fstream> FileInterface::openFileToRead(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;

    if (!isFileExists(fileName, pathToFile))
    {
        std::cerr << "File " + fileName + " does not exist in the selected location. " << std::endl;
        return nullptr; //TODO mwozniak error
    }

    if (getFileAccess(fileName, pathToFile))
    {
        FileFlag::setFileFlag(FileFlagType::guardian, pathToFile, fileName);
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }

    std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();
    fileToOpen->open(fileLocation, std::ios::in);

    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }
}

std::unique_ptr<std::fstream> FileInterface::openFileToSave(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;

    if (!isFileExists(fileName, pathToFile))
    {
        std::cerr << "File " + fileName + " does not exist in the selected location. " << std::endl;
        return nullptr; //TODO mwozniak errror
    }

    if (getFileAccess(fileName, pathToFile))
    {
        FileFlag::setFileFlag(FileFlagType::guardian, pathToFile, fileName);
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }

    std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();
    fileToOpen->open(fileLocation, std::ios::out | std::ios::app);

    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }
}


bool FileInterface::removeFile(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    const char * c = fileLocation.c_str();
    return ! std::remove(c); // 0 when success
    //TODO mwozniak mnurzynski czy moze usuwac systemowo przez rm ?
}


std::unique_ptr<std::vector<std::string>> FileInterface::getFileContent(const std::string& fileName, const std::string& pathToFile)
{
    std::unique_ptr<std::vector<std::string>> fileContent = std::make_unique<std::vector<std::string>>();

    if (std::unique_ptr<std::fstream> file = openFileToRead(fileName, pathToFile))
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
        return nullptr;
        //TODO mwozniak error + removeGuard
    }
                                      //TODO mwozniak mnurzyn
    closeFile(fileName, pathToFile); //close file usuwa guardiana, moze jednak jakas nazwa na to?
    //nie potrzebujemy funkcji ktora wykonuje operacje zamykania bo wykonuje sie to w memencie destrukcji obiektu fstream
    return fileContent;
}

std::unique_ptr<std::string> FileInterface::removeRowField(const std::string& row, const int fieldNumber)
{
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


bool FileInterface::removeRow(const std::string& fileName, const std::string& pattern, const std::string& pathToFile)
{    
    if (!getFileAccess(fileName, pathToFile))
    {
        return false;
    }

    FileFlag::setFileFlag(FileFlagType::guardian, pathToFile, fileName);
    const std::string fileLocation = pathToFile + fileName;
    std::string command = "sed -i -e '/" + pattern + "/d' " + fileLocation;
    std::system(command.c_str());

    bool isFileClosed = closeFile(fileName, pathToFile);

    return isFileClosed;
}


bool FileInterface::updateRow(const std::string & fileName, const std::string & newRow, const std::string & where, const std::string & pathToFile)
{
    if (!getFileAccess(fileName))
    {
        return false;
    }
    const std::string fileLocation = pathToFile + fileName;
    FileFlag::setFileFlag(FileFlagType::guardian, pathToFile, fileName);
    std::string command = "sed -i -e 's/.*" + where + ".*/" + newRow + "/g' " + fileLocation;
    //TODO mwozniak ^zeby podmienialo tylko pierwsze znalezione wystapienie
    std::system(command.c_str());

    bool isFileClosed = closeFile(fileName, pathToFile);

    return isFileClosed;
}


std::unique_ptr<std::string> FileInterface::updateRowField(const std::string& row, const std::string& newField, const int fieldNumber)
{
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


std::string System::getActualDateTime()
{
    std::string dateTime = __DATE__;
    dateTime += "|";
    dateTime += __TIME__;
    return dateTime;
}

std::string System::getStdoutFromCommand(std::string cmd)
{
    std::string data;
    FILE * stream;
    const int max_buffer = 256;
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
