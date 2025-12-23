#pragma once
#include <string>
#include <iostream>
#include "../include/logger.hpp"

using std::string;
extern Logger logger;

class Person {
protected:
    string name;

public:
    Person(const string& name = "");
    virtual ~Person();

    inline string getName() const { return name; }
    inline void setName(const string& n) { name = n; }
};
