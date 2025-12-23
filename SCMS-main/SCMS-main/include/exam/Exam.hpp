#pragma once
#include <string>
#include <map>
#include <ctime>
#include <iostream>

using std::string, std::map;

class Exam {
private:
    string courseID;
    time_t date;
    int maxMarks;
    map<string, int> studentMarks; // student username -> marks

public:
    Exam() = default;
    Exam(const string& course, time_t d, int max);

    string getCourseID() const;
    time_t getDate() const;
    int getMaxMarks() const;

    void setMark(const string& student, int marks);
    int getMark(const string& student) const;
    const map<string,int>& getAllMarks() const;

    // Relational operator for sorting
    bool operator<(const Exam& other) const; 
};
