#pragma once
#include <string>
#include <fstream>

using std::string;

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
private:
    std::ofstream fout;
    LogLevel level;
    bool consoleOutput;
    string getTimestamp() const;

public:
    Logger(LogLevel lvl = LogLevel::INFO);
    ~Logger();

    void init(const string& filepath);
    void log(LogLevel lvl, const string& module, const std::string& message);
    void close();
};
