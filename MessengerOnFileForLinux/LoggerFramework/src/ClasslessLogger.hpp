#pragma once
#include <iostream>

void fileLog(const char * logData, const char * logSpace)
{
    FILE* logFile;
    logFile = fopen("Logger_default.txt", "a");
    if (!logFile)
    {
        std::cout << "logFile open failed!" << std::endl;
        exit(1);
    }

    fprintf(logFile, "\n%s %s %s \t %s\n", __DATE__, __TIME__, logSpace, logData);

    fclose(logFile);
}
