#include <iostream>
#include <filesystem>
#include <limits>
#include <memory>
#include "../include/logger.hpp"
#include "../include/authmanager.hpp"
#include "../include/person/Student.hpp"
#include "../include/person/Teacher.hpp"
#include "../include/person/Admin.hpp"
#include "../include/course/CourseManager.hpp"
#include "../include/attendance/AttendanceManager.hpp"
#include "../include/exam/ExamManager.hpp"
#include "../include/library/LibraryManager.hpp"
using namespace std;

namespace fs = filesystem;

// Global Logger
Logger logger;

// Role-Based Menu
void showRoleMenu(UserRole role, const string& username,AuthManager& auth, 
                  CourseManager& cm, AttendanceManager& am,
                  ExamManager& em, LibraryManager& lm) {
    bool logout = false;
    while (!logout) {
        int choice = 0;

        cout << "\n============================= SCMS - " << username << " ==============================\n";

        if (role == UserRole::ADMIN) {
            cout << "1. Course Management\n2. Attendance Management\n3. Exam Management\n4. Library Management\n5. Create User\n6. Change Password\n7. Logout\nChoice: ";
        } else if (role == UserRole::TEACHER) {
            cout << "1. Attendance Management\n2. Exam Management\n3. Change Password\n4. Logout\nChoice: ";
        } else { // STUDENT
            cout << "1. View Courses\n2. View Attendance\n3. View Exam Reports\n4. Library Services\n5. Change Password\n6. Logout\nChoice: ";
        }

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (role) {
            case UserRole::ADMIN:
    switch (choice) {

        case 1:
            cm.menu();
            break;

        case 2:
            am.menu(username);
            break;

        case 3:
            em.menu();
            break;

        case 4:
            lm.menu();
            break;

        case 5: { // Create User
            int typeChoice;
            string newUsername, password;

            cout << "\nCreate User Type:\n";
            cout << "1. Student\n2. Teacher\n3. Admin\nChoice: ";
            if (!(cin >> typeChoice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input\n";
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            UserRole role;
            if (typeChoice == 1) role = UserRole::STUDENT;
            else if (typeChoice == 2) role = UserRole::TEACHER;
            else if (typeChoice == 3) role = UserRole::ADMIN;
            else {
                cout << "Invalid role selection\n";
                break;
            }

            cout << "Enter username: ";
            getline(cin, newUsername);

            cout << "Enter password: ";
            getline(cin, password);

            try {
                auth.createUserByAdmin(username, newUsername, password, role);
                cout << "User created successfully!\n";
                logger.log(LogLevel::INFO, "AUTH",
                           "Admin created user: " + newUsername);
            }
            catch (const AuthException& e) {
                cout << "Error: " << e.what() << "\n";
                logger.log(LogLevel::ERROR, "AUTH", e.what());
            }

            break;
        }

        case 6: { // Change Password
            string oldPass, newPass, confirmPass;

            cout << "Enter current password: ";
            getline(cin, oldPass);

            try {
                auth.login(username, oldPass);
            }
            catch (...) {
                cout << "Incorrect current password\n";
                break;
            }

            cout << "Enter new password: ";
            getline(cin, newPass);

            cout << "Confirm new password: ";
            getline(cin, confirmPass);

            if (newPass != confirmPass) {
                cout << "Passwords do not match\n";
                break;
            }

            auth.changePassword(username, newPass);
            cout << "Password changed successfully\n";
            logger.log(LogLevel::INFO, "AUTH",
                       username + " changed password");
            break;
        }

        case 7:
            logout = true;
            break;

        default:
            cout << "Invalid choice\n";
    }
    break;


            case UserRole::TEACHER:
                switch (choice) {
                    case 1: am.menu(username); break;
                    case 2: em.menu(); break;
                    case 3: {  // Change Password
                        string oldPass, newPass, confirmPass;
                        cout << "Enter current password: ";
                        getline(cin, oldPass);
                        try {
                            if (!auth.login(username, oldPass)) { cout << "Incorrect password\n"; break; }
                        } catch (const AuthException& e) { cout << e.what() << "\n"; break; }

                        cout << "Enter new password: "; getline(cin, newPass);
                        cout << "Confirm new password: "; getline(cin, confirmPass);
                        if (newPass != confirmPass) { cout << "Passwords do not match\n"; break; }

                        auth.changePassword(username, newPass);
                        cout << "Password changed successfully\n";
                        break;
                    }
                    case 4: logout = true; break;
                    default: cout << "Invalid choice\n";
                }
                break;

            case UserRole::STUDENT:
                switch (choice) {
                    case 1: cm.viewCourses(); break;
                    case 2: am.viewAttendance(username); break;
                    case 3: em.viewReports(username); break;
                    case 4: lm.studentMenu(username); break;
                    case 5: {  // Change Password
                        string oldPass, newPass, confirmPass;
                        cout << "Enter current password: ";
                        getline(cin, oldPass);
                        try {
                            if (!auth.login(username, oldPass)) { cout << "Incorrect password\n"; break; }
                        } catch (const AuthException& e) { cout << e.what() << "\n"; break; }

                        cout << "Enter new password: "; getline(cin, newPass);
                        cout << "Confirm new password: "; getline(cin, confirmPass);
                        if (newPass != confirmPass) { cout << "Passwords do not match\n"; break; }

                        auth.changePassword(username, newPass);
                        cout << "Password changed successfully\n";
                        break;
                    }
                    case 6: logout = true; break;
                    default: cout << "Invalid choice\n";
                }
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        // Paths Setup
        fs::path exeDir = fs::absolute(argv[0]).parent_path();
        fs::path projectRoot = exeDir.parent_path().parent_path();
        fs::path logFile = projectRoot / "logs" / "scms.log";
        fs::path dataDir = projectRoot / "data";

        fs::create_directories(logFile.parent_path());
        fs::create_directories(dataDir);

        // Initialize Logger
        logger.init(logFile.string());
        logger.log(LogLevel::INFO, "SYSTEM", "System started.");

        string instituteName;
        cout << "===============================================================================================\n";
        cout << "                                 SMART CAMPUS MANAGEMENT SYSTEM\n";
        cout << "===============================================================================================\n";
        cout << "Enter Institute Name: ";
        getline(cin, instituteName);
        logger.log(LogLevel::INFO, "SYSTEM", "Institute: " + instituteName);

        // Managers
        AuthManager auth((dataDir / "users.dat").string());
        CourseManager cm((dataDir / "courses.dat").string());
        AttendanceManager am((dataDir / "attendance").string());
        ExamManager em((dataDir / "exam").string());
        LibraryManager lm((dataDir / "library").string());

        // Authentication Menu
        string loggedInUser;
        bool running = true;
        while (running) {
            cout << "\n\n\n\n================================= SCMS - " << instituteName << " ====================================\n";
            cout << "1. Login\n2. Exit\nChoice: ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: { // Login
                    string username, password;
                    cout << "Username: "; getline(cin, username);
                    cout << "Password: "; getline(cin, password);

                    try {
                        if (auth.login(username, password)) {
                            loggedInUser = username;
                            UserRole role = auth.getLoggedInUserRole();
                            logger.log(LogLevel::INFO, "AUTH", username + " logged in.");
                            showRoleMenu(role, loggedInUser, auth, cm, am, em, lm);
                        }
                    } catch (const AuthException& e) {
                        cout << "Auth error: " << e.what() << "\n";
                        logger.log(LogLevel::ERROR, "AUTH", e.what());
                    }
                    break;
                }
                case 2: { // Exit
                    logger.log(LogLevel::INFO, "SYSTEM", "System exited.");
                    running = false;
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    logger.log(LogLevel::WARNING, "MAIN", "Invalid menu choice");
            }
        }

        logger.close();
        return 0;
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        logger.log(LogLevel::ERROR, "MAIN", e.what());
        return 1;
    } catch (...) {
        cerr << "Unknown fatal error occurred" << endl;
        logger.log(LogLevel::ERROR, "MAIN", "Unknown fatal error");
        return 1;
    }
}
