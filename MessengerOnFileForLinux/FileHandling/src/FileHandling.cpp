#include "FileHandling.hpp"
#include "FileGuardian.hpp"
#include <iostream>
#include <cstdlib>



bool addRow(const  std::string & fileName, const std::string & text, const std::string & pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    if (std::unique_ptr< std::fstream> file = openFileToSave(fileLocation))
    {
        *file << text;
        *file << '\n';
        closeFile(fileLocation);
        return true;
    }
    else
    {
        return false;
        //TODO error
        //skad wiemy czy plik nieistenije czy jest guearian?
    }
}


bool closeFile(const std::string & fileToClose, const std::string & pathToFile)
{    
    guard::removeFileFlag(fileToClose, FileFlagType::guardian, pathToFile);
}

bool createFile(const std::string & fileName, const std::string & pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    std::ofstream fileToCreate(fileLocation);
    fileToCreate << " ";
    return isFileExists(fileName, pathToFile);
}

bool getFileAccess(const std::string & fileName, const std::string & pathToFile)
{
    return guard::isGuardExist(fileName, FileFlagType::guardian, pathToFile);
}

std::unique_ptr< std::string> getRowField(const std::string & field, const int fieldNumber)
{
    int actualFieldNumber = -1;
    std::unique_ptr< std::string> fieldToDownload = std::make_unique<std::string>();
    for (auto &x : field)
    {
        if ('[' == x)
        {
            ++actualFieldNumber;
            continue;
        }

        if (actualFieldNumber == fieldNumber && ']' != x)
        {
            fieldToDownload -> push_back(x);
        }
    }
    return fieldToDownload;
}

bool isFileExists(const std::string & fileName, const std::string & pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    std::ifstream file(fileLocation);
    return file.good();
}

std::unique_ptr <std::fstream> openFileToRead(const std::string & fileName, const std::string & pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;

    if (!isFileExists(fileName, pathToFile))
    {
        std::cerr << "File " + fileName + " does not exist in the selected location. " << std::endl;
        return nullptr; //TODO error
    }
    if (getFileAccess(fileName, pathToFile))
        guard::setFileFlag(fileName, FileFlagType::guardian, pathToFile);
    else
        return nullptr;

    std::unique_ptr <std::fstream> fileToOpen= std::make_unique< std::fstream>();
    fileToOpen->open(fileLocation, std::ios::in);

    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        return nullptr;
    }
}

std::unique_ptr <std::fstream> openFileToSave(const std::string & fileName, const std::string & pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;

    if (!isFileExists(fileName, pathToFile))
    {
        std::cerr << "File " + fileName + " does not exist in the selected location. " << std::endl;
        return nullptr; //TODO error
    }
    if (getFileAccess(fileName, pathToFile))
        guard::setFileFlag(fileName, FileFlagType::guardian, pathToFile);
    else
        return nullptr;

    std::unique_ptr <std::fstream> fileToOpen= std::make_unique< std::fstream>();
    fileToOpen->open(fileLocation, std::ios::out | std::ios::app);

    if (fileToOpen->is_open())
    {
        return fileToOpen;
    }
    else
    {
        return nullptr;
    }
}


bool removeFile(const std::string & fileName, const std::string & pathToFile)
{
    const std::string fileLocation = pathToFile + fileName;
    const char * c = fileLocation.c_str();
    return ! std::remove(c); // 0 when success
}


std::unique_ptr< std::vector< std::string>> returnFileContent(const std::string & fileName, const std::string & pathToFile)
{
    std::unique_ptr< std::vector< std::string>> fileContent = std::make_unique< std::vector< std::string>>();

    if (std::unique_ptr< std::fstream> file = openFileToRead(fileName, pathToFile))
    {
        while (!file->eof())
        {
            std::string row; //osobna funkcja na to ?
            std::getline(*file, row);
            fileContent -> push_back(row);
        }
    }
    else
    {
        return nullptr;
        //TODO error + removeGuard
    }
    //file juz tu nie istnieje, wiec plik zostal zamkiety
    closeFile(fileName, pathToFile); //close file usuwa guardiana, jak to nazwac?
    return fileContent;
}

std::unique_ptr<std::string> removeRowField(const std::string & row, const int fieldNumber)
{
    int actualFieldNumber = -1;
    std::unique_ptr< std::string> rowWithoutRemovedField = std::make_unique<std::string>();
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


bool removeRow(const std::string & fileName, const std::string pattern, const std::string & pathToFile)
{    
    if (!getFileAccess(fileName, pathToFile))
    {
        return false;
    }

    const std::string fileLocation = pathToFile + fileName;
    guard::setFileFlag(fileName, FileFlagType::guardian, pathToFile);
    std::string command = "sed -i -e '/" + pattern + "/d' " + fileLocation;
    std::system(command.c_str());
    closeFile(fileName, pathToFile);
    return true;

}


bool updateRow(const std::string & fileName, const std::string & newRow, const std::string & where, const std::string & pathToFile)
{
    if (!getFileAccess(fileName))
    {
        return false;
    }
    const std::string fileLocation = pathToFile + fileName;
    guard::setFileFlag(fileName, FileFlagType::guardian);
    std::string command = "sed -i -e 's/.*" + where + ".*/" + newRow + "/g' " + fileLocation;
    std::system(command.c_str());
    closeFile(fileName, pathToFile);
    return true;

}


std::unique_ptr<std::string> updateRowField(const std::string & row, const std::string & newField, const int fieldNumber)
{
    int actualFieldNumber = -1;
    bool flag = false;
    std::unique_ptr< std::string> rowToUpdate = std::make_unique<std::string>();
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

            for (auto &y : newField)
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

std::string getEnviromentalVariable( const std::string & var ) //gdzie indziej to dac
{
    const char * val = ::getenv( var.c_str() );
    if ( val == 0 ) {
        return "";
    }
    else {
        return val;
    }
}

std::string getActualDateTime()
{
    std::string dateTime = __DATE__;
    dateTime += "|";
    dateTime += __TIME__;
    return dateTime;
}
