#include "Logger.h"

// ANSI color codes
const std::string Logger::RESET = "\033[0m";
const std::string Logger::RED = "\033[31m";
const std::string Logger::GREEN = "\033[32m";
const std::string Logger::YELLOW = "\033[33m";
const std::string Logger::BLUE = "\033[34m";
const std::string Logger::MAGENTA = "\033[35m";
const std::string Logger::CYAN = "\033[36m";
const std::string Logger::WHITE = "\033[37m";
const std::string Logger::BOLD = "\033[1m";

void Logger::info(const std::string& message) {
    std::cout << BLUE << "[INFO] " << RESET << message << std::endl;
}

void Logger::success(const std::string& message) {
    std::cout << GREEN << "[SUCCESS] " << RESET << message << std::endl;
}

void Logger::warning(const std::string& message) {
    std::cout << YELLOW << "[WARNING] " << RESET << message << std::endl;
}

void Logger::error(const std::string& message) {
    std::cout << RED << "[ERROR] " << RESET << message << std::endl;
}

void Logger::pump(const std::string& message) {
    std::cout << MAGENTA << "[PUMP] " << RESET << message << std::endl;
}

void Logger::sensor(const std::string& message) {
    std::cout << CYAN << "[SENSOR] " << RESET << message << std::endl;
}

void Logger::system(const std::string& message) {
    std::cout << BOLD << WHITE << "[SYSTEM] " << RESET << message << std::endl;
}
