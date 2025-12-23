#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <ctime>

using std::vector, std::string, std::time_t;

class AttendanceRecord {
private:
    string studentUsername;
    string courseID;
    time_t date; // store date as time_t
    bool present;

public:
    AttendanceRecord() = default;
    AttendanceRecord(const string& student, const string& course, time_t d, bool p);

    string getStudent() const;
    string getCourse() const;
    time_t getDate() const;
    bool isPresent() const;

    void setPresent(bool p);

    // Operator Overloading
    friend std::ostream& operator<<(std::ostream& os, const AttendanceRecord& record);
    friend std::istream& operator>>(std::istream& is, AttendanceRecord& record);
    bool operator==(const AttendanceRecord& other) const; // compare date + student + course
};
