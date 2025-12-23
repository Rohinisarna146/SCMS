#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>

using std::string;

enum class UserRole {
    ADMIN = 1,
    TEACHER,
    STUDENT
};

class AuthException : public std::runtime_error {
public:
    explicit AuthException(const string& msg)
        : std::runtime_error(msg) {}
};

class AuthManager {
private:
    string filePath;

    std::unordered_map<string, std::pair<string, UserRole>> users;

    string loggedInUser;
    string hashPassword(const string& password);
    void loadUsers();
    void saveUsers();

public:
    explicit AuthManager(const string& path);

    // Authentication
    bool login(const string& username, const string& password);
    void logout();

    // ADMIN-ONLY user creation
    void createUserByAdmin(const string& adminUsername,
                           const string& newUsername,
                           const string& password,
                           UserRole role);

    // Password
    void changePassword(const string& username,
                        const string& newPassword);

    // Info
    UserRole getUserRole(const string& username) const;
    UserRole getLoggedInUserRole() const;
    string getLoggedInUsername() const;
};
