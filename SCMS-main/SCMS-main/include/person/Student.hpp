#pragma once
#include "../include/person/User.hpp"

using std::string;

class Student : public User {
private:
    string studentID;

public:
    Student(const string& name = "");
    virtual ~Student();
};
