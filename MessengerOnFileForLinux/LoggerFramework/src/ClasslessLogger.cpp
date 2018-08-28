#include <ClasslessLogger.hpp>

void fileLog(const char * logData, const char * logSpace)
{
    FILE* logFile;
    logFile = fopen("Logger_default.txt", "a");
    if (!logFile)
    {
        std::cout << "logFile open failed!" << std::endl;
        exit(1);
    }

    fprintf(logFile, "%s %s %s %s  %s\n",std::getenv("USER"), __DATE__, __TIME__, logSpace, logData);

    fclose(logFile);
}
