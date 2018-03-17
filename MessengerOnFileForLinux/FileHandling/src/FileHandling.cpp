#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include <FileHandling.hpp>

bool FileInterface::Modification::addRow(const std::string& fileName, const std::string& pathToFile, const std::string& text)
{
    if (std::unique_ptr<std::fstream> file = Managment::openFileToSave(fileName, pathToFile))
    {
        *file << text;
        *file << '\n';
        Managment::removeFile("GUARD", pathToFile);
        return true;
    }
    else
    {
        return false;
        //TODO mwozniak error
        //skad wiemy czy plik nie istenije czy jest guardian?
    }
}


bool FileInterface::Managment::createFile(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    std::string systemCommand = "touch " + fileLocation;
    system(systemCommand.c_str());

    return isFileExist(fileName, pathToFile);
}

std::unique_ptr<std::vector<std::string>> FileInterface::Accesor::getFileContent(const std::string& fileName, const std::string& pathToFile)
{
    std::unique_ptr<std::vector<std::string>> fileContent = std::make_unique<std::vector<std::string>>();

    if (std::unique_ptr<std::fstream> file = Managment::openFileToRead(fileName, pathToFile))
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

    Managment::removeFile("GUARD", pathToFile);

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

bool FileInterface::Managment::isFileExist(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    std::ifstream file(fileLocation);
    return file.good();
}

std::unique_ptr<std::fstream> FileInterface::Managment::openFileToRead(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;

    if (!isFileExist(fileName, pathToFile))
    {
        std::cerr << "File " + fileName + " does not exist in the selected location. " << std::endl;
        return nullptr; //TODO mwozniak error
    }

    if (!isFileExist("GUARD", pathToFile))
    {
        createFile("GUARD", pathToFile);
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

std::unique_ptr<std::fstream> FileInterface::Managment::openFileToSave(const std::string& fileName, const std::string& pathToFile)
{
    if (!isFileExist(fileName, pathToFile))
    {
        std::cerr << "File " + fileName + " does not exist in the selected location. " << std::endl;
        return nullptr; //TODO mwozniak errror
    }

    if (!isFileExist("GUARD", pathToFile))
    {
        createFile("GUARD", pathToFile);
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }

    std::string fileLocation = pathToFile + fileName;
    std::unique_ptr<std::fstream> fileToOpen= std::make_unique<std::fstream>();
    fileToOpen->open(fileLocation, std::ios::out | std::ios::ate);

    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        return nullptr; //TODO mwozniak errror
    }
}


bool FileInterface::Managment::removeFile(const std::string& fileName, const std::string& pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    std::cout << "Usuwam : " << fileLocation << std::endl;
    const char * c = fileLocation.c_str();
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


bool FileInterface::Modification::removeRow(const std::string& fileName, const std::string& pathToFile, const std::string& pattern)
{    
    if (Managment::isFileExist("GUARD", pathToFile))
    {
        return false;
    }

    Managment::createFile("GUARD", pathToFile);

    const std::string fileLocation = pathToFile + fileName;
    std::string command = "sed -i -e '/" + pattern + "/d' " + fileLocation;
    std::system(command.c_str());

    bool isGuardRemoved = Managment::removeFile("GUARD", pathToFile);

    return isGuardRemoved;
}


bool FileInterface::Modification::updateRow(const std::string & fileName, const std::string & pathToFile, const std::string & newRow, const std::string & where)
{
    if (Managment::isFileExist("GUARD", pathToFile))
    {
        return false;
    }

    Managment::createFile("GUARD", pathToFile);

    const std::string fileLocation = pathToFile + fileName;
    std::string command = "sed -i -e 's/.*" + where + ".*/" + newRow + "/g' " + fileLocation;
    //TODO mwozniak ^zeby podmienialo tylko pierwsze znalezione wystapienie
    std::system(command.c_str());

    bool isGuardRemoved = Managment::removeFile("GUARD", pathToFile);

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
