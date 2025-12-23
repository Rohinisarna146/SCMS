#include "../include/exam/ExamManager.hpp"
#include "../include/logger.hpp"
#include "../include/exam/ReportGenerator.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

extern Logger logger;
namespace fs = filesystem;

ExamManager::ExamManager(const string& dir) : dataDir(dir) {
    fs::create_directories(dataDir);
    loadExamData();
}

void ExamManager::addExam(const Exam& exam) {
    exams.push_back(exam);
    saveExamData(exam);
    logger.log(LogLevel::INFO, "EXAM", "Added exam for course " + exam.getCourseID());
}

void ExamManager::enterMarks(const string& courseID, const string& student, int marks) {
    
    auto it = find_if(exams.begin(), exams.end(), [&](const Exam& e){ return e.getCourseID() == courseID; });
    if (it != exams.end()) {
        it->setMark(student, marks);
        saveExamData(*it);
    } else {
        throw runtime_error("Exam not found for course " + courseID);
    }
}

vector<Exam> ExamManager::getExams(const string& courseID) const {
    vector<Exam> result;
    for (auto& e : exams) if (e.getCourseID() == courseID) result.push_back(e);
    return result;
}

void ExamManager::saveExamData(const Exam& exam) {
    fs::path file = fs::path(dataDir) / ("exam_" + exam.getCourseID() + ".dat");
    ofstream fout(file, ios::binary);
    for (auto& [student, marks] : exam.getAllMarks()) {
        fout << student << " " << marks << "\n";
    }
    fout.close();
    logger.log(LogLevel::INFO, "EXAM", "Saved exam data for " + exam.getCourseID());
}

void ExamManager::loadExamData() {
    for (auto& p : fs::directory_iterator(dataDir)) {
        if (p.path().extension() == ".dat") {
            ifstream fin(p.path());
            string courseID = p.path().stem().string().substr(5); // remove "exam_"
            Exam e(courseID, time(nullptr), 100); // default max 100
            string student; int marks;
            while (fin >> student >> marks) e.setMark(student, marks);
            exams.push_back(e);
        }
    }
}


void ExamManager::menu() {
    int choice;

    while (true) {
        cout << "\n--- Exams Menu ---\n";
        cout << "1. Add Exam\n";
        cout << "2. Enter Marks\n";
        cout << "3. View Exam Report\n";
        cout << "4. Back\n";
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 4) break;

        switch (choice) {

            case 1: { // Add Exam
                string courseID;
                int day, month, year, maxMarks;

                cout << "Course ID: ";
                getline(cin, courseID);

                cout << "Exam Date (DD MM YYYY): ";
                cin >> day >> month >> year;
                cin.ignore();

                cout << "Max Marks: ";
                cin >> maxMarks;
                cin.ignore();

                tm tm_date{};
                tm_date.tm_year = year - 1900;
                tm_date.tm_mon  = month - 1;
                tm_date.tm_mday = day;

                time_t date = mktime(&tm_date);

                addExam(Exam(courseID, date, maxMarks));
                cout << "Exam added successfully.\n";
                break;
            }

            case 2: { // Enter Marks
                string courseID, student;
                int marks;

                cout << "Course ID: ";
                getline(cin, courseID);

                cout << "Student Username: ";
                getline(cin, student);

                cout << "Marks: ";
                cin >> marks;
                cin.ignore();

                try {
                    enterMarks(courseID, student, marks);
                    cout << "Marks entered successfully.\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }

            case 3: { // View Exam Report
                string courseID;
                cout << "Course ID: ";
                getline(cin, courseID);

                auto exams = getExams(courseID);
                if (exams.empty()) {
                    cout << "No exams found for this course.\n";
                    break;
                }

                cout << "Select Exam:\n";
                for (size_t i = 0; i < exams.size(); ++i) {
                    time_t d = exams[i].getDate();
                    tm* tm_ptr = localtime(&d);
                    cout << i << ": "
                              << put_time(tm_ptr, "%d-%m-%Y") << "\n";
                }

                int index;
                cin >> index;
                cin.ignore();

                if (index < 0 || index >= static_cast<int>(exams.size())) {
                    cout << "Invalid exam selection.\n";
                    break;
                }

                auto& exam = exams[index];

                vector<pair<string, int>> marksData(
                    exam.getAllMarks().begin(),
                    exam.getAllMarks().end()
                );

                ReportGenerator<pair<string, int>> report(marksData);
                report.sortByMarks();

                cout << "\n--- Exam Report ---\n";
                report.printReport();
                break;
            }

            default:
                cout << "Invalid choice\n";
        }
    }
}


void ExamManager::viewReports(const string& studentUsername) const {
    cout << "\n--- Exam Reports for " << studentUsername << " ---\n";

    bool found = false;
    for (const auto& exam : exams) {
        auto marksMap = exam.getAllMarks(); 
        auto it = marksMap.find(studentUsername);
        if (it != marksMap.end()) {
            time_t d = exam.getDate();
            tm* tm_ptr = localtime(&d);
            cout << "Course: " << exam.getCourseID()
                      << ", Date: " << put_time(tm_ptr, "%d-%m-%Y")
                      << ", Marks: " << it->second
                      << "/" << exam.getMaxMarks() << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No exam records found for this student.\n";
    }
}

