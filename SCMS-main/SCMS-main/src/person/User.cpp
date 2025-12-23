#include "../include/person/User.hpp"
using namespace std;

User::User(const string& name)
    : Person(name) {
    logger.log(LogLevel::INFO, "USER", "User created: " + name);
}

User::~User() {
    logger.log(LogLevel::INFO, "USER", "User destroyed: " + name);
}
