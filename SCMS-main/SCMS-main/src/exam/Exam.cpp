#include "../include/exam/Exam.hpp"
#include "../include/logger.hpp"
#include <stdexcept>
using namespace std;

extern Logger logger;

Exam::Exam(const string& course, time_t d, int max)
    : courseID(course), date(d), maxMarks(max) {}

string Exam::getCourseID() const { return courseID; }
time_t Exam::getDate() const { return date; }
int Exam::getMaxMarks() const { return maxMarks; }

void Exam::setMark(const string& student, int marks) {
    if (marks < 0 || marks > maxMarks) {
        throw invalid_argument("Marks out of range");
    }
    studentMarks[student] = marks;
    logger.log(LogLevel::INFO, "EXAM", "Set marks for " + student + " in " + courseID);
}

int Exam::getMark(const string& student) const {
    auto it = studentMarks.find(student);
    if (it != studentMarks.end()) return it->second;
    return -1; // marks not entered yet
}

const map<string,int>& Exam::getAllMarks() const { return studentMarks; }

bool Exam::operator<(const Exam& other) const {
    return date < other.date; // sorting exams by date
}
