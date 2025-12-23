#include "../include/person/Admin.hpp"
#include "../include/logger.hpp"
using namespace std;

Admin::Admin(const string& name)
    : User(name) {
    logger.log(LogLevel::INFO, "ADMIN", "Admin created: " + name);
}

Admin::~Admin() {
    logger.log(LogLevel::INFO, "ADMIN", "Admin destroyed: " + name);
}
