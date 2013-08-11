#include "Logger.hpp"

const int Logger::LOG_INFO    = 0;
const int Logger::LOG_WARNING = 1;
const int Logger::LOG_ERROR   = 2;

void Logger::log(int type, std::string message){
    switch (type) {
        case Logger::LOG_INFO:
            std::cout << "[INFO] ";
            break;
        case Logger::LOG_WARNING:
            std::cout << "\e[33m[WARNING] ";
            break;
        case Logger::LOG_ERROR:
            std::cout << "\e[31m[ERROR] ";
            break;
        default:
            Logger::log(LOG_ERROR, "Log type not found");
            break;
    }
    std::cout << message << "\e[m" << std::endl;
}

void Logger::log(std::string message){
    Logger::log(Logger::LOG_INFO, message);
}
