#include "../include/person/Teacher.hpp"
#include "../include/logger.hpp"
using namespace std;

extern Logger logger;

Teacher::Teacher(const string& name)
    : User(name) {
    logger.log(LogLevel::INFO, "TEACHER", "Teacher created: " + name);
}

Teacher::~Teacher() {
    logger.log(LogLevel::INFO, "TEACHER", "Teacher destroyed: " + name);
}
