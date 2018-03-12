#pragma once
#include<memory>
#include<vector>
#include<string>
#include<fstream>

bool addRow(const  std::string & fileName, const std::string & text, const std::string & pathToFile = "");
bool closeFile(const std::string & fileToClose, const std::string & pathToFile = "");
bool createFile(const std::string & fileName, const std::string & pathToFile = "");
bool getFileAccess(const std::string & fileName, const std::string & pathToFile = "");
std::unique_ptr< std::string> getRowField(const std::string & field, const int fieldNumber);
bool isFileExists(const std::string & fileName, const std::string & pathToFile = "");
std::unique_ptr <std::fstream> openFileToRead(const std::string & fileName, const std::string & pathToFile = "");
std::unique_ptr <std::fstream> openFileToSave(const std::string & fileName, const std::string & pathToFile = "");
std::unique_ptr<std::string> removeRowField(const std::string & row, const int fieldNumber);
std::unique_ptr< std::vector< std::string>> returnFileContent(const std::string & fileName, const std::string & pathToFile = "");
bool removeRow(const std::string & fileName, const std::string pattern, const std::string & pathToFile = "");
bool removeFile(const std::string & fileName, const std::string & pathToFile = "");
bool updateRow(const std::string & fileName, const std::string & newRow, const std::string & where, const std::string & pathToFile = "");
std::unique_ptr<std::string> updateRowField(const std::string & row, const std::string & newField, const int fieldNumber);

std::unique_ptr< std::vector< std::string>> getFilesNames(const std::string& pathToDir = "");

/** wrzucic to gdzie indzie*/
std::string getEnviromentVariable( const std::string & var ); //DONE
std::string getActualDateTime();//DONE
std::string getStdoutFromCommand(std::string cmd);


