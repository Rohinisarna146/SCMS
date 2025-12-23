#include "../include/course/CourseManager.hpp"
#include "../include/logger.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

extern Logger logger;

CourseManager::CourseManager(const string& file) : filename(file) {
    loadCourses();
}

void CourseManager::loadCourses() {
    ifstream fin(filename); // text mode
    if (!fin.is_open() || fin.peek() == ifstream::traits_type::eof()) {
        logger.log(LogLevel::INFO, "COURSE", "No courses loaded, starting fresh");
        return;
    }

    courses.clear();
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string id, title;
        int credits, capacity, nstudents;

        getline(iss, id, ',');
        getline(iss, title, ',');
        iss >> credits >> capacity >> nstudents;

        Course c(id, title, credits, capacity);

        for (int i = 0; i < nstudents; ++i) {
            string student;
            iss >> student;
            c.enrollStudent(student);
        }

        courses.push_back(c);
    }

    logger.log(LogLevel::INFO, "COURSE", to_string(courses.size()) + " courses loaded");
    fin.close();
}

void CourseManager::saveCourses() {
    ofstream fout(filename); // text mode

    for (auto& c : courses) {
        fout << c.getID() << "," << c.getTitle() << ","
             << c.getCredits() << " " << c.getCapacity() << " "
             << c.getEnrolled().size();

        for (auto& s : c.getEnrolled()) {
            fout << " " << s;
        }
        fout << "\n";
    }

    fout.close();
    logger.log(LogLevel::INFO, "COURSE", "Courses saved to file");
}

bool CourseManager::addCourse(const Course& c) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& x){ return x.getID() == c.getID(); });
    if (it != courses.end()) return false;
    courses.push_back(c);
    saveCourses();
    logger.log(LogLevel::INFO, "COURSE", "Added course: " + c.getID());
    return true;
}

bool CourseManager::updateCourse(const string& courseID, const Course& updated) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& x){ return x.getID() == courseID; });
    if (it == courses.end()) return false;
    *it = updated;
    saveCourses();
    logger.log(LogLevel::INFO, "COURSE", "Updated course: " + courseID);
    return true;
}

bool CourseManager::deleteCourse(const string& courseID) {
    auto it = remove_if(courses.begin(), courses.end(), [&](const Course& x){ return x.getID() == courseID; });
    if (it == courses.end()) return false;
    courses.erase(it, courses.end());
    saveCourses();
    logger.log(LogLevel::INFO, "COURSE", "Deleted course: " + courseID);
    return true;
}

bool CourseManager::enrollStudent(const string& courseID, const string& username) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& x){ return x.getID() == courseID; });
    if (it == courses.end()) return false;
    bool res = it->enrollStudent(username);
    saveCourses();
    logger.log(LogLevel::INFO, "COURSE", "Enroll student " + username + " in " + courseID);
    return res;
}

bool CourseManager::dropStudent(const string& courseID, const string& username) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& x){ return x.getID() == courseID; });
    if (it == courses.end()) return false;
    bool res = it->dropStudent(username);
    saveCourses();
    logger.log(LogLevel::INFO, "COURSE", "Drop student " + username + " from " + courseID);
    return res;
}

void CourseManager::listCourses() const {
    for (auto& c : courses) c.printCourse();
}


void CourseManager::menu() {
    int choice;
    while (true) {
        cout << "\n--- Course Menu ---\n";
        cout << "1. List Courses\n2. Add Course\n3. Update Course\n4. Delete Course\n5. Enroll Student\n6. Drop Student\n7. Back\nChoice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();
        if (choice == 7) break;

        string id, title, username;
        int credits, capacity;
        switch (choice) {
            case 1: listCourses(); break;
            case 2:
                cout << "ID: "; getline(cin, id);
                cout << "Title: "; getline(cin, title);
                cout << "Credits: "; cin >> credits;
                cout << "Capacity: "; cin >> capacity; cin.ignore();
                addCourse(Course(id, title, credits, capacity));
                break;
            case 3:
                cout << "ID to update: "; getline(cin, id);
                cout << "New Title: "; getline(cin, title);
                cout << "New Credits: "; cin >> credits;
                cout << "New Capacity: "; cin >> capacity; cin.ignore();
                updateCourse(id, Course(id, title, credits, capacity));
                break;
            case 4: 
                cout << "ID to delete: "; getline(cin, id);
                deleteCourse(id);
                break;
            case 5:
                cout << "Course ID: "; getline(cin, id);
                cout << "Student username: "; getline(cin, username);
                enrollStudent(id, username);
                break;
            case 6:
                cout << "Course ID: "; getline(cin, id);
                cout << "Student username: "; getline(cin, username);
                dropStudent(id, username);
                break;
            default: cout << "Invalid choice!\n"; break;
        }
    }
}

void CourseManager::viewCourses() const {
    cout << "\n--- Courses Available ---\n";
    listCourses();
}
