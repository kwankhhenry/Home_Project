#pragma once
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

struct structlog {
    bool header = true;
    bool type = true;
    bool timestamp = true;
    typelog level = WARN;
};

extern structlog LOGCFG;

class LOG
{
public:
    LOG() = delete;
    LOG(typelog msglevel){
        std::string filename = "log_" + get_time("%Y%m%d") + ".txt";
        _logOutput = std::ofstream(filename, std::ofstream::app);
        if(LOGCFG.header) {
            operator<< (get_header(msglevel) + "- ");
        }
    };
    LOG& operator=(LOG& rhs) = delete;

    template <typename T>
    std::ofstream& operator<<(const T input){
        if(_logOutput.is_open())
            _logOutput << input;
        return _logOutput;
    };

    ~LOG()
    {
        _logOutput.close();
    };

private:
    inline std::string getLabel(typelog type) {
        std::string label;
        switch(type) {
            case DEBUG: label = "[DEBUG]"; break;
            case INFO:  label = "[INFO]"; break;
            case WARN:  label = "[WARN]"; break;
            case ERROR: label = "[ERROR]"; break;
        }
        return label;
    }

    inline std::string get_time(const char* format)
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        //2047-03-11 20:18:26
        oss << std::put_time(&tm, format);
        return oss.str();
    }

    inline std::string get_header(typelog type)
    {
        std::stringstream oss;
        if(LOGCFG.type)
            oss << std::setw(7) << getLabel(type) << " ";

        if(LOGCFG.timestamp)
            oss << std::setw(19) << std::left << get_time("%Y-%m-%d-%H:%M:%S") << " ";

        return oss.str();
    }
    std::ofstream _logOutput;
};