#include "Logger.h"

#include <ios>
#include <string>


static const char* fileName = "log";

Logger::Logger(std::string loggerName): loggerName(loggerName)
{
    file.open(fileName);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Logging file couldn't be opened");
    }
}

std::ostream& Logger::operator<<(std::string msg)
{
    return file << loggerName << ": " << std::string(msg) << std::endl;
}
