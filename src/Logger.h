#include <fstream>
#include <iostream>


class Logger
{
public:
    Logger(std::string loggerName);
    std::ostream& operator<<(std::string msg);
private:
    std::string loggerName;
    std::ofstream file;
};
