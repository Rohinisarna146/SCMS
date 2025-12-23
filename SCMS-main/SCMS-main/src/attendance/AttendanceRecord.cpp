#include "../include/attendance/AttendanceRecord.hpp"
#include <iomanip>
#include <sstream>
using namespace std;

AttendanceRecord::AttendanceRecord(const string& student, const string& course, time_t d, bool p)
    : studentUsername(student), courseID(course), date(d), present(p) {}

string AttendanceRecord::getStudent() const { return studentUsername; }
string AttendanceRecord::getCourse() const { return courseID; }
time_t AttendanceRecord::getDate() const { return date; }
bool AttendanceRecord::isPresent() const { return present; }

void AttendanceRecord::setPresent(bool p) { present = p; }

ostream& operator<<(ostream& os, const AttendanceRecord& record) {
    tm* tm_ptr = localtime(&record.date);
    os << record.studentUsername << " "
       << record.courseID << " "
       << put_time(tm_ptr, "%d-%m-%Y") << " "
       << record.present;
    return os;
}

istream& operator>>(istream& is, AttendanceRecord& record) {
    string dateStr;
    is >> record.studentUsername >> record.courseID >> dateStr >> record.present;

    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%d-%m-%Y");
    record.date = mktime(&tm);

    return is;
}

bool AttendanceRecord::operator==(const AttendanceRecord& other) const {
    return studentUsername == other.studentUsername &&
           courseID == other.courseID &&
           date == other.date;
}
