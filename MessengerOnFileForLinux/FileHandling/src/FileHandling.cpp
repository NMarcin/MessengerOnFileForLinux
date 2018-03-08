#include "FileHandling.hpp"
#include "FileGuardian.hpp"
#include <iostream>
#include <cstdlib>



bool addRow(const  std::string & fileName, const std::string & text)
{
    if (std::unique_ptr< std::fstream> file = openFileToSave(fileName))
    {
        *file << text;
        *file << '\n';
        closeFile(fileName);
        return true;
    }
    else
    {
        return false;
        //TODO error
        //skad wiemy czy plik nieistenije czy jest guearian?
    }
}

std::unique_ptr< std::string> addBracketsToStrings(std::string obj, ...)
{
    std::unique_ptr< std::string> stringsWithBrackets = std::make_unique<std::string>();
    std::va_list args;
    va_start(args, obj);

    //while (*obj != '\0')
   // {

    //}
}

bool closeFile(const std::string & fileToClose)
{
    guard::removeFileFlag(fileToClose, FileFlagType::guardian);
}

bool createFile(const std::string & fileName)
{
    std::ofstream fileToCreate(fileName);
    fileToCreate << " ";
    return isFileExists(fileName);
}

bool getFileAccess(const std::string & fileName)
{
    return guard::isGuardExist(fileName, FileFlagType::guardian);
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

bool isFileExists(const std::string & fileName)
{
    std::ifstream file(fileName);
    return file.good();
}

std::unique_ptr <std::fstream> openFileToRead(const std::string & fileName)
{
    if (!isFileExists(fileName))
    {
        std::cerr << "File " + fileName + " does not exist" << std::endl;
        return nullptr; //TODO error
    }
    if (getFileAccess(fileName))
        guard::setFileFlag(fileName, FileFlagType::guardian);
    else
        return nullptr;

    std::unique_ptr <std::fstream> fileToOpen= std::make_unique< std::fstream>();
    fileToOpen->open(fileName, std::ios::in);
    if (fileToOpen->is_open())
        return fileToOpen;
    else
        return nullptr;
}

std::unique_ptr <std::fstream> openFileToSave(const std::string & fileName)
{
    if (!isFileExists(fileName))
    {
        std::cerr << "File " + fileName + " does not exist" << std::endl;
        return nullptr; //TODO error
    }
    if (getFileAccess(fileName))
        guard::setFileFlag(fileName, FileFlagType::guardian);
    else
        return nullptr;

    std::unique_ptr <std::fstream> fileToOpen= std::make_unique< std::fstream>();
    fileToOpen->open(fileName, std::ios::out | std::ios::app);
    if (fileToOpen->is_open())
        return fileToOpen;
    else
        return nullptr;
}


bool removeFile(const std::string & fileName)
{
    const char * c = fileName.c_str();
    return ! std::remove(c); // 0 when success
}


std::unique_ptr< std::vector< std::string>> returnFileContent(const std::string & fileName)
{
    std::unique_ptr< std::vector< std::string>>
            fileContent = std::make_unique< std::vector< std::string>>();

    if (std::unique_ptr< std::fstream> file = openFileToRead(fileName))
    {
        while (!file->eof())
        {
            std::string row; //osobna funkcja na to
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
    closeFile(fileName); //close file usuwa guardiana, jak to nazwac?
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


bool removeRow(const std::string & fileName, const std::string pattern)
{
    if (getFileAccess(fileName))
    {
        guard::setFileFlag(fileName, FileFlagType::guardian);
        std::string command = "sed -i -e '/" + pattern + "/d' " + fileName;
        std::system(command.c_str());
        closeFile(fileName);
        return true;
    }
    else
        return false;
}


bool updateRow(const std::string & fileName, const std::string & newRow, const std::string & where)
{
    if (getFileAccess(fileName))
    {
        guard::setFileFlag(fileName, FileFlagType::guardian);
        std::string command = "sed -i -e 's/.*" + where + ".*/" + newRow + "/g' " + fileName;
        std::system(command.c_str());
        closeFile(fileName);
        return true;
    }
    else
        return false;
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
