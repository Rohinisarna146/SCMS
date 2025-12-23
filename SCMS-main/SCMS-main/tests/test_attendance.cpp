#include "../include/attendance/AttendanceManager.hpp"
#include "../include/logger.hpp"
#include <ctime>
#include <cassert>
#include <iostream>

Logger logger;

int main() {
    AttendanceManager am("test_attendance");

    std::time_t today = std::time(nullptr);
    am.markAttendance("student1", "CS101", today, true);

    auto records = am.getAttendance("CS101", today, today);
    assert(!records.empty());

    std::cout << "Attendance tests passed\n";
    return 0;
}
