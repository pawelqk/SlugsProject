#include "Logger.h"

#include <ios>
#include <string>

namespace
{
    const char* fileName = "log";
    bool isOpen = false;
}

Logger::Logger(std::string loggerName): loggerName(loggerName)
{
    if (!isOpen)
    {
        file.open(fileName);
        isOpen = true;
    }
    else
    {
        file.open(fileName, std::ios::app);
    }

    if (!file.is_open())
    {
        throw std::ios_base::failure("Logging file couldn't be opened");
    }
}

std::ofstream& Logger::operator()(LoggingLevel level)
{
    file << loggerName;

    switch(level)
    {
    case LoggingLevel::INFO:
        file << " [INFO] ";
        break;
    case LoggingLevel::DEBUG:
        file << " [DEBUG] ";
        break;
    case LoggingLevel::ERROR:
        file << " [ERROR] ";
        break;
    }

    return file;
}