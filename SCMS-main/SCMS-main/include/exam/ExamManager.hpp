#pragma once
#include "../include/exam/Exam.hpp"
#include <vector>
#include <string>
#include <ctime>

using std::vector, std::string;

class ExamManager {
private:
    vector<Exam> exams;
    string dataDir; // folder for exam files

public:
    ExamManager() = default;
    ExamManager(const string& dir);

    void addExam(const Exam& exam);
    void enterMarks(const string& courseID, const string& student, int marks);
    vector<Exam> getExams(const string& courseID) const;
    void saveExamData(const Exam& exam);
    void loadExamData(); // load all exams from files
    void menu(); // full access for teacher/admin
    void viewReports(const string& studentUsername) const; // student view only

};
