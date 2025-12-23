cmake_minimum_required(VERSION 3.10)
project(SCMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------- Include Directories -----------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ----------------- Source Files -----------------
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/person/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/course/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/attendance/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exam/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/library/*.cpp
)

# ----------------- Executable -----------------
add_executable(scms ${SRC_FILES})

# ----------------- Output Directories -----------------
set_target_properties(scms PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build/release
)

# ----------------- Create Data & Logs folders post-build -----------------
add_custom_command(TARGET scms POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build/data
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build/logs
)


# ----------------- TESTING -----------------
enable_testing()

# -------- Auth Manager Test --------
add_executable(test_auth
    tests/test_auth.cpp
    src/authmanager.cpp
    src/logger.cpp
)
target_include_directories(test_auth PRIVATE include)
add_test(NAME AuthTest COMMAND test_auth)


# -------- Course Management Test --------
add_executable(test_course
    tests/test_course.cpp
    src/course/Course.cpp
    src/course/Coursemanager.cpp
    src/logger.cpp
)
target_include_directories(test_course PRIVATE include)
add_test(NAME CourseTest COMMAND test_course)


# -------- Attendance Management Test --------
add_executable(test_attendance
    tests/test_attendance.cpp
    src/attendance/AttendanceRecord.cpp
    src/attendance/AttendanceManager.cpp
    src/logger.cpp
)
target_include_directories(test_attendance PRIVATE include)
add_test(NAME AttendanceTest COMMAND test_attendance)


# -------- Exam Management Test --------
add_executable(test_exam
    tests/test_exam.cpp
    src/exam/Exam.cpp
    src/exam/ExamManager.cpp
    src/logger.cpp
)
target_include_directories(test_exam PRIVATE include)
add_test(NAME ExamTest COMMAND test_exam)


# -------- Library Management Test --------
add_executable(test_library
    tests/test_library.cpp
    src/library/Book.cpp
    src/library/LibraryManager.cpp
    src/logger.cpp
)
target_include_directories(test_library PRIVATE include)
add_test(NAME LibraryTest COMMAND test_library)
