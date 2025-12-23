#include "../include/course/Course.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Course::Course(const string& id, const string& t, int c, int cap)
    : courseID(id), title(t), credits(c), capacity(cap) {}

string Course::getID() const { return courseID; }
string Course::getTitle() const { return title; }
int Course::getCredits() const { return credits; }
int Course::getCapacity() const { return capacity; }
vector<string> Course::getEnrolled() const { return enrolledStudents; }

void Course::setTitle(const string& t) { title = t; }
void Course::setCredits(int c) { credits = c; }
void Course::setCapacity(int cap) { capacity = cap; }

bool Course::enrollStudent(const string& username) {
    if (enrolledStudents.size() >= capacity) return false;
    if (find(enrolledStudents.begin(), enrolledStudents.end(), username) != enrolledStudents.end())
        return false;
    enrolledStudents.push_back(username);
    return true;
}

bool Course::dropStudent(const string& username) {
    auto it = find(enrolledStudents.begin(), enrolledStudents.end(), username);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);
        return true;
    }
    return false;
}

void Course::printCourse() const {
    cout << "Course ID: " << courseID
              << ", Title: " << title
              << ", Credits: " << credits
              << ", Capacity: " << capacity
              << ", Enrolled: " << enrolledStudents.size() << endl;
}
