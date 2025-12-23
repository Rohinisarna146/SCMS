#pragma once
#include "../include/person/Person.hpp"

using std::string;

class User : public Person {
public:
    User(const string& name = "");
    virtual ~User();
};
