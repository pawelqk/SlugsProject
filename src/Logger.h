#include <fstream>
#include <iostream>


enum LoggingLevel: uint8_t
{
    INFO,
    DEBUG,
    ERROR
};

class Logger
{
public:
    Logger(std::string loggerName);

    std::ofstream& operator()(LoggingLevel level);

private:
    std::string loggerName;
    std::ofstream file;
};
