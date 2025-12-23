#include "../include/person/Student.hpp"
#include "../include/logger.hpp"
using namespace std;

extern Logger logger;

Student::Student(const string& name)
    : User(name), studentID(studentID) {
    logger.log(LogLevel::INFO, "STUDENT", "Student created: " + name);
}

Student::~Student() {
    logger.log(LogLevel::INFO, "STUDENT", "Student destroyed: " + name);
}
