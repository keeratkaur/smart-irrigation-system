#pragma once
#include <iostream>
#include <string>

class Logger {
public:
    // ANSI color codes
    static const std::string RESET;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string BOLD;
    
    // Logging methods
    static void info(const std::string& message);
    static void success(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
    static void pump(const std::string& message);
    static void sensor(const std::string& message);
    static void system(const std::string& message);
};
