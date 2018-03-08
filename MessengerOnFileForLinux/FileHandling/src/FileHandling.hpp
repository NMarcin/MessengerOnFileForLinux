#pragma once
#include<memory>
#include<vector>
#include<string>
#include<fstream>
#include <cstdarg>

bool addRow(const  std::string & fileName, const std::string & text);
std::unique_ptr< std::string> addBracketsToStrings(std::string obj, ...);
bool closeFile(const std::string & fileToClose);
bool createFile(const std::string & fileName);
bool getFileAccess(const std::string & fileName);
std::unique_ptr< std::string> getRowField(const std::string & field, const int fieldNumber);
bool isFileExists(const std::string & fileName);
std::unique_ptr <std::fstream> openFileToRead(const std::string & fileName);
std::unique_ptr <std::fstream> openFileToSave(const std::string & fileName);
std::unique_ptr<std::string> removeRowField(const std::string & row, const int fieldNumber);
std::unique_ptr< std::vector< std::string>> returnFileContent(const std::string & fileName);
bool removeRow(const std::string & fileName, const std::string pattern);
bool removeFile(const std::string & fileName);
bool updateRow(const std::string & fileName, const std::string & newRow, const std::string & where);
std::unique_ptr<std::string> updateRowField(const std::string & row, const std::string & newField, const int fieldNumber);


/** wrzucic to gdzie indzie*/
std::string getEnviromentalVariable( const std::string & var ); //DONE
std::string getActualDateTime();//DONE


