#include "../include/person/Person.hpp"
#include "../include/logger.hpp"
using namespace std;

extern Logger logger;

Person::Person(const string& name)
    : name(name) {
    logger.log(LogLevel::INFO, "PERSON", "Person created: " + name);
}

Person::~Person() {
    logger.log(LogLevel::INFO, "PERSON", "Person destroyed: " + name);
}
