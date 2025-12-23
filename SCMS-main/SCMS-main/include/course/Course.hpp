#pragma once
#include <string>
#include <vector>

using std::vector, std::string;

class Course {
private:
    string courseID;
    string title;
    int credits;
    int capacity;
    vector<string> enrolledStudents; // usernames (students)

public:
    Course() = default;
    Course(const string& id, const string& t, int c, int cap);

    // Getters
    string getID() const;
    string getTitle() const;
    int getCredits() const;
    int getCapacity() const;
    vector<string> getEnrolled() const;

    // Setters
    void setTitle(const string& t);
    void setCredits(int c);
    void setCapacity(int cap);

    // Enrollment
    bool enrollStudent(const string& username);
    bool dropStudent(const string& username);

    // Display
    void printCourse() const;
};
