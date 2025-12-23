#pragma once
#include "../include/attendance/AttendanceRecord.hpp"
#include <vector>
#include <string>
#include <ctime>

using std::vector, std::string, std::time_t;

class AttendanceManager {
private:
    vector<AttendanceRecord> records;
    string dataDir; // folder to store attendance files

    string getFilenameForDate(time_t date) const;

public:
    AttendanceManager() = default;
    AttendanceManager(const string& dir);

    void loadAttendance(time_t date);
    void saveAttendance(time_t date);

    void markAttendance(const string& student, const string& course, time_t date, bool present);
    vector<AttendanceRecord> getAttendance(const string& courseID, time_t fromDate, time_t toDate) const;
    void menu(const string& teacherUsername); // mark attendance (view for teacher/admin)
    void viewAttendance(const string& studentUsername) const; // read-only view for student

};
