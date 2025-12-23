#include "../include/exam/ExamManager.hpp"
#include "../include/logger.hpp"
#include <ctime>
#include <cassert>
#include <iostream>

Logger logger;

int main() {
    ExamManager em("test_exam");

    std::time_t date = std::time(nullptr);
    em.addExam(Exam("CS101", date, 100));
    em.enterMarks("CS101", "student1", 80);

    auto exams = em.getExams("CS101");
    assert(!exams.empty());

    std::cout << "Exam tests passed\n";
    return 0;
}
