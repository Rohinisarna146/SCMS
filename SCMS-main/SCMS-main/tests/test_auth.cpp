#include "../include/authmanager.hpp"
#include "../include/logger.hpp"
#include <cassert>
#include <functional>
#include <iostream>

Logger logger;

int main() {
    AuthManager auth("../data/users.dat");

    // Default admin should exist
    assert(auth.login("admin", "admin123") == true);

    // Change password
    auth.changePassword("admin", "newadmin");
    assert(auth.login("admin", "newadmin") == true);
    std::cout << "Auth tests passed\n";
    return 0;
}
