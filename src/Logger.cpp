#include "Logger.h"

#include <iostream>
#include <chrono>
#include <iomanip>

void Logger::log(const std::string& level,
                 const std::string& msg)
{
    auto now = std::chrono::system_clock::now();

    auto t = std::chrono::system_clock::to_time_t(now);

    std::tm* tm = std::localtime(&t);

    std::cout
        << "["
        << std::put_time(tm,"%H:%M:%S")
        << "] "
        << "[" << level << "] "
        << msg
        << std::endl;
}

void Logger::info(const std::string& msg)
{
    log("INFO ", msg);
}

void Logger::warning(const std::string& msg)
{
    log("WARN ", msg);
}

void Logger::error(const std::string& msg)
{
    log("ERROR", msg);
}
