#pragma once
#include "Course.hpp"
#include <vector>
#include <string>

using std::vector, std::string;

class CourseManager {
private:
    vector<Course> courses;
    string filename;

public:
    CourseManager() = default;
    CourseManager(const string& file);

    void loadCourses();
    void saveCourses();

    bool addCourse(const Course& c);
    bool updateCourse(const string& courseID, const Course& updated);
    bool deleteCourse(const string& courseID);

    bool enrollStudent(const string& courseID, const string& username);
    bool dropStudent(const string& courseID, const string& username);

    void listCourses() const;
    // For admin/teacher
    void menu(); 

    // For students
    void viewCourses() const;

};
