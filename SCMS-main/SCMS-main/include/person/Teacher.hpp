#pragma once
#include "../include/person/User.hpp"

using std::string;

class Teacher : public User {
public:
    Teacher(const string& name = "");
    virtual ~Teacher();
};
