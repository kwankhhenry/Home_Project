#include <iostream>
#include <sstream>

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger
{
public:
    // Copy constructor
    Logger(Logger& copy) = delete;

    // Accesser to get instance
    static Logger& Get_Instance()
    {
        return s_Instance;
    }    

    void printStream()
    {
        std::string debugMsg;
        switch(debugType)
        {
            case(DEBUG): debugMsg = "DEBUG"; break;
            case(INFO): debugMsg = "INFO"; break;
            case(WARN): debugMsg = "WARN"; break;
            case(ERROR): debugMsg = "WARN"; break;
        }
        std::cout << "[LOG " << debugMsg << "] " << oss.str();
    }

    // Overload insertion operator
    template <typename T>
    Logger& operator<<(const T& msg)
    {
        oss << msg << " ";
        return *this;
    }

    // Overload << that detects function (i.e. std::endl of type std::ostream&)
    Logger& operator<<(std::ostream& (*manip)(std::ostream&))
    {
        oss << manip;
        printStream();
        oss.str("");
        return *this;
    }

private:
    // Constructor
    Logger(){};
    ~Logger(){ std::cout << "Destructor Called" << std::endl; };
    static Logger s_Instance;
    std::ostringstream oss;
    typelog debugType;
};

Logger Logger::s_Instance;

int main()
{
    Logger& LogDebug = Logger::Get_Instance();
    LogDebug << "test" << 3 << "20423" << std::endl;
    LogDebug << "test2" << 5 << 342.232 << std::endl;

    return 0;
}