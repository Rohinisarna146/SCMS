#pragma once
#include "../include/person/User.hpp"

using std::string;

class Admin : public User {
private:
    int accessLevel;

public:
    Admin(const string& name = "");
    virtual ~Admin();
};
