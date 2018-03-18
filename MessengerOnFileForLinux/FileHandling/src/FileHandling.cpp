#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include <FileHandling.hpp>

bool FileInterface::Modification::addRow(const std::string& pathToFile, const std::string& text)
{
    if (std::unique_ptr<std::fstream> file = Managment::openFileToSave(pathToFile))
    {
        *file << text;
        *file << '\n';
        std::string folderName = *Accesor::getFolderName(pathToFile);
        Managment::removeFile(folderName + "/GUARD");
        return true;
    }
    else
    {
        return false;
        //TODO mwozniak error
        //skad wiemy czy plik nie istenije czy jest guardian?
    }
}


bool FileInterface::Managment::createFile(const std::string& pathToFile)
{
    std::string systemCommand = "touch " + pathToFile;
    system(systemCommand.c_str());

    return isFileExist(pathToFile);
}

std::unique_ptr<std::vector<std::string>> FileInterface::Accesor::getFileContent(const std::string& pathToFile)
{
    std::unique_ptr<std::vector<std::string>> fileContent = std::make_unique<std::vector<std::string>>();

    if (std::unique_ptr<std::fstream> file = Managment::openFileToRead(pathToFile))
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

    std::string folderName = *Accesor::getFolderName(pathToFile);
    Managment::removeFile(folderName + "/GUARD");

    return fileContent;
}

std::unique_ptr<std::vector<std::string>> FileInterface::Accesor::getFilenamesFromFolder(const std::string& pathToDir)
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

std::unique_ptr<std::string> FileInterface::Accesor::getFolderName(const std::string& pathToFile)
{
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

bool FileInterface::Managment::isFileExist(const std::string& pathToFile)
{
    std::ifstream file(pathToFile);
    return file.good();
}

std::unique_ptr<std::fstream> FileInterface::Managment::openFileToRead(const std::string& pathToFile)
{
    if (!isFileExist(pathToFile))
    {
        std::cerr << pathToFile + " does not exist. " << std::endl;
        return nullptr; //TODO mwozniak error
    }

    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (!isFileExist(folderName + "/GUARD"))
    {
        createFile(folderName + "/GUARD");
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }

    std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();
    fileToOpen->open(pathToFile, std::ios::in);
    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }
}

std::unique_ptr<std::fstream> FileInterface::Managment::openFileToSave(const std::string& pathToFile)
{
    if (!isFileExist(pathToFile))
    {
        std::cerr << pathToFile + " does not exist. " << std::endl;
        return nullptr; //TODO mwozniak errror
    }

    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (!isFileExist(folderName + "/GUARD"))
    {
        createFile(folderName + "/GUARD");
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }


    std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();
    fileToOpen->open(pathToFile, std::ios::out | std::ios::ate);

    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }
}


bool FileInterface::Managment::removeFile(const std::string& pathToFile)
{
    const char * c = pathToFile.c_str();
    return ! std::remove(c); // 0 when success
    //TODO mwozniak mnurzynski czy moze usuwac systemowo przez rm ?
}



std::unique_ptr<std::string> FileInterface::Modification::removeRowField(const std::string& row, const int fieldNumber)
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


bool FileInterface::Modification::removeRow(const std::string& pathToFile, const std::string& pattern)
{    
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
    std::string folderName = *Accesor::getFolderName(pathToFile);

    if (Managment::isFileExist(folderName + "/GUARD"))
    {
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
