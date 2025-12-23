#include "../include/course/CourseManager.hpp"
#include "../include/logger.hpp"
#include <iostream>


Logger logger;

int main() {
    CourseManager cm("test_courses.dat");

    cm.addCourse(Course("CS101", "C++ Programming", 4, 50));
    cm.listCourses();

    std::cout << "Course tests passed\n";
    return 0;
}
