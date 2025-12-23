#include "../include/authmanager.hpp"
#include <fstream>
#include <sstream>
#include <functional>
using namespace std;


// Constructor
AuthManager::AuthManager(const string& path)
    : filePath(path) {
    loadUsers();

    // Default admin creation
    if (users.empty()) {
        users["admin"] = { hashPassword("admin123"), UserRole::ADMIN };
        saveUsers();
    }

}

// Load Users
void AuthManager::loadUsers() {
    users.clear();
    ifstream fin(filePath);
    if (!fin.is_open()) return;

    string username, password;
    int role;
    while (fin >> username >> password >> role) {
        users[username] = { password, static_cast<UserRole>(role)};
    }
}

// Save Users
void AuthManager::saveUsers() {
    ofstream fout(filePath, ios::trunc);
    if (!fout.is_open())
        throw AuthException("Unable to write users file");

    for (auto& [user, data] : users) {
        fout << user << " "
             << data.first << " "
             << static_cast<int>(data.second) << "\n";
    }
}

// Login
bool AuthManager::login(const string& username,
                        const string& password) {
    auto it = users.find(username);
    if (it == users.end())
        throw AuthException("User does not exist");

    if (it->second.first != hashPassword(password))
        throw AuthException("Incorrect password");

    loggedInUser = username;
    return true;
}

// Logout
void AuthManager::logout() {
    loggedInUser.clear();
}

// ADMIN creates users
void AuthManager::createUserByAdmin(const string& adminUsername,
                                    const string& newUsername,
                                    const string& password,
                                    UserRole role) {
    // Check admin privilege
    auto adminIt = users.find(adminUsername);
    if (adminIt == users.end() ||
        adminIt->second.second != UserRole::ADMIN) {
        throw AuthException("Only admin can create users");
    }

    if (users.count(newUsername))
        throw AuthException("Username already exists");

    users[newUsername] = { hashPassword(password), role };

    saveUsers();
}

// Change Password
void AuthManager::changePassword(const string& username,
                                 const string& newPassword) {
    auto it = users.find(username);
    if (it == users.end())
        throw AuthException("User not found");

    it->second.first = hashPassword(newPassword);
    saveUsers();
}

// Get Role
UserRole AuthManager::getUserRole(const string& username) const {
    auto it = users.find(username);
    if (it == users.end())
        throw AuthException("User not found");
    return it->second.second;
}

UserRole AuthManager::getLoggedInUserRole() const {
    if (loggedInUser.empty())
        throw AuthException("No user logged in");
    return getUserRole(loggedInUser);
}

string AuthManager::getLoggedInUsername() const {
    return loggedInUser;
}

string AuthManager::hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}
