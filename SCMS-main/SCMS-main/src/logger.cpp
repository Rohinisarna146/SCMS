#include "../include/logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
using namespace std;

Logger::Logger(LogLevel lvl)
    : level(lvl) {}

Logger::~Logger() {
    close();
}

void Logger::init(const string& filepath) {
    fout.open(filepath, ios::app);
    if (!fout.is_open()) {
        throw runtime_error("Failed to open log file: " + filepath);
    }
    log(LogLevel::INFO, "LOGGER", "Logger initialized.");
}

void Logger::log(LogLevel lvl, const string& module, const string& message) {
    if (!fout.is_open()) return;

    string lvlStr;
    switch (lvl) {
        case LogLevel::INFO: lvlStr = "INFO"; break;
        case LogLevel::WARNING: lvlStr = "WARNING"; break;
        case LogLevel::ERROR: lvlStr = "ERROR"; break;
    }

    string logMsg = "[" + getTimestamp() + "] [" + lvlStr + "] [" + module + "] " + message;
    fout << logMsg << endl;
    if (consoleOutput) {
        cout << logMsg << endl;
    }
}

void Logger::close() {
    if (fout.is_open()) {
        log(LogLevel::INFO, "LOGGER", "Logger closed.");
        fout.close();
    }
}

string Logger::getTimestamp() const {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    tm tm_buf;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_buf, &time);
#else
    localtime_r(&time, &tm_buf);
#endif
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_buf);
    return string(buffer);
}
