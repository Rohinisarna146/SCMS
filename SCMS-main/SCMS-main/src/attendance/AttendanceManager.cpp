#include "../include/attendance/AttendanceManager.hpp"
#include "../include/attendance/AttendanceRecord.hpp"
#include "../include/logger.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
using namespace std;

extern Logger logger;
namespace fs = filesystem;

AttendanceManager::AttendanceManager(const string& dir) : dataDir(dir) {
    fs::create_directories(dataDir); // ensure folder exists
}

string AttendanceManager::getFilenameForDate(time_t date) const {
    tm* tm_ptr = localtime(&date);
    ostringstream oss;
    oss << dataDir << "/attendance_" << put_time(tm_ptr, "%d-%m-%Y") << ".dat";
    return oss.str();
}

void AttendanceManager::loadAttendance(time_t date) {
    string file = getFilenameForDate(date);
    ifstream fin(file);
    if (!fin.is_open()) return;

    AttendanceRecord rec;
    records.clear();
    while (fin >> rec) {
        records.push_back(rec);
    }
    fin.close();
}

void AttendanceManager::saveAttendance(time_t date) {
    string file = getFilenameForDate(date);
    ofstream fout(file);
    for (auto& rec : records) {
        fout << rec << endl;
    }
    fout.close();
    logger.log(LogLevel::INFO, "ATTENDANCE", "Attendance saved for date " + to_string(date));
}

void AttendanceManager::markAttendance(const string& student, const string& course, time_t date, bool present) {
    AttendanceRecord rec(student, course, date, present);
    // check if record exists
    auto it = find(records.begin(), records.end(), rec);
    if (it != records.end()) it->setPresent(present);
    else records.push_back(rec);

    saveAttendance(date);
    logger.log(LogLevel::INFO, "ATTENDANCE", "Marked " + student + " as " + (present ? "present" : "absent") + " in " + course);
}

vector<AttendanceRecord> AttendanceManager::getAttendance(const string& courseID, time_t fromDate, time_t toDate) const {
    vector<AttendanceRecord> result;
    for (const auto& rec : records) {
        if (rec.getCourse() == courseID && rec.getDate() >= fromDate && rec.getDate() <= toDate) {
            result.push_back(rec);
        }
    }
    return result;
}


void AttendanceManager::menu(const string& teacherUsername) {
    int choice;

    while (true) {
        cout << "\n--- Attendance Menu ---\n";
        std::cout << "1. Mark Attendance\n";
        std::cout << "2. View Attendance\n";
        std::cout << "3. Back\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 3) break;

        std::string courseID, studentUsername;
        int day, month, year;
        std::tm tm_date{};
        std::time_t date;

        switch (choice) {
            case 1: { // Mark Attendance
                std::cout << "Course ID: ";
                std::getline(std::cin, courseID);

                std::cout << "Student Username: ";
                std::getline(std::cin, studentUsername);

                std::cout << "Date (DD MM YYYY): ";
                std::cin >> day >> month >> year;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                tm_date.tm_year = year - 1900;
                tm_date.tm_mon = month - 1;
                tm_date.tm_mday = day;
                tm_date.tm_hour = 0;
                tm_date.tm_min = 0;
                tm_date.tm_sec = 0;

                date = std::mktime(&tm_date);

                char present;
                std::cout << "Present? (y/n): ";
                std::cin >> present;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                markAttendance(
                    studentUsername,
                    courseID,
                    date,
                    (present == 'y' || present == 'Y')
                );

                std::cout << "Attendance marked successfully.\n";
                break;
            }

            case 2: { // View Attendance
                std::cout << "Course ID: ";
                std::getline(std::cin, courseID);

                std::cout << "From Date (DD MM YYYY): ";
                std::cin >> day >> month >> year;
                std::cin.ignore();

                tm_date.tm_year = year - 1900;
                tm_date.tm_mon = month - 1;
                tm_date.tm_mday = day;
                std::time_t fromDate = std::mktime(&tm_date);

                std::cout << "To Date (DD MM YYYY): ";
                std::cin >> day >> month >> year;
                std::cin.ignore();

                tm_date.tm_year = year - 1900;
                tm_date.tm_mon = month - 1;
                tm_date.tm_mday = day;
                std::time_t toDate = std::mktime(&tm_date);

                auto records = getAttendance(courseID, fromDate, toDate);

                if (records.empty()) {
                    std::cout << "No attendance records found.\n";
                    break;
                }

                for (auto& r : records) {
                    std::time_t d = r.getDate();
                    std::tm* tm_ptr = std::localtime(&d);

                    std::cout << r.getStudent() << " | "
                              << r.getCourse() << " | "
                              << std::put_time(tm_ptr, "%d-%m-%Y") << " | "
                              << (r.isPresent() ? "Present" : "Absent")
                              << "\n";
                }
                break;
            }

            default:
                std::cout << "Invalid choice\n";
        }
    }
}

void AttendanceManager::viewAttendance(const std::string& studentUsername) const {
    std::cout << "\n--- Attendance for " << studentUsername << " ---\n";

    bool found = false;
    for (const auto& record : records) { // std::vector<AttendanceRecord> records;
        if (record.getStudent() == studentUsername) {
            std::time_t date = record.getDate();
            std::tm* tm_ptr = std::localtime(&date);
            std::cout << "Course: " << record.getCourse()
                      << ", Date: " << std::put_time(tm_ptr, "%d-%m-%Y")
                      << ", Status: " << (record.isPresent() ? "Present" : "Absent") << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No attendance records found for this student.\n";
    }
}
