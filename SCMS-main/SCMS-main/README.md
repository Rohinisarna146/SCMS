# Smart Campus Management System (SCMS)

A console-based **Smart Campus Management System** developed in **C++**.
This project manages campus-level academic and administrative activities such as **user authentication, courses, attendance, examinations, and library management** using object-oriented programming principles.

---

## Features

* User authentication (Admin / Teacher / Student)
* Secure password storage using hashing
* Role-based access control
* Course creation, update, enrollment, and deletion
* Attendance management with date-wise records
* Examination and marks management with reports
* Library management (issue and return books)
* File-based persistent storage
* Centralized logging system

---

## Project Structure

```bash
SCMS/
│
├── build/
├── data/
│   ├── users.dat
│   ├── courses.dat
│   ├── attendance/
│    │   └── attendance_DD-MM-YYYY
│   ├── exam/
│   └── library/
│
├── include/
│   ├── attendance/
│   │   ├── AttendanceManager.hpp
│   │   └── AttendanceRecord.hpp
│   ├── course/
│   │   ├── Course.hpp
│   │   └── CourseManager.hpp
│   ├── exam/
│   │   ├── Exam.hpp
│   │   ├── ExamManager.hpp
│   │   └── ReportGenerator.hpp
│   ├── library/
│   │   ├── Book.hpp
│   │   └── LibraryManager.hpp
│   ├──  person/
│   │   ├── Person.hpp
│   │   ├── Student.hpp
│   │   ├── Teacher.hpp
│   │   ├── User.hpp
│   │   └── Admin.hpp
│   ├── authmanager.hpp
│   └── logger.hpp
│
├── logs/
│   └── scms.log
│
├── src/
│   ├── attendance/
│   │   ├── AttendanceManager.cpp
│   │   └── AttendanceRecord.cpp
│   ├── course/
│   │   ├── Course.cpp
│   │   └── CourseManager.cpp
│   ├── exam/
│   │   ├── Exam.cpp
│   │   └── ExamManager.cpp
│   ├── library/
│   │   ├── Book.cpp
│   │   └── LibraryManager.cpp
│   ├── person/
│   │   ├── User.cpp
│   │   ├── Person.cpp
│   │   ├── Student.cpp
│   │   ├── Teacher.cpp
│   │   └── Admin.cpp
│   ├── main.cpp
│   ├── authmanager.cpp
│   └── logger.cpp
├── tests/
│   │   ├── test_attendance.cpp
│   │   ├── test_auth.cpp
│   │   ├── test_course.cpp
│   │   ├── test_exam.cpp
│   │   └── test_library.cpp
├── CMakeLists.txt
├── gitignore
└── README.md
```

---

## Technologies Used

* C++17
* Standard Template Library (STL)
* CMake
* File handling (`fstream`)

---

## Requirements

* C++ Compiler (GCC / Clang / MSVC)
* CMake 3.15 or above
* Windows / Linux OS

---

## Build & Run

### Using CMake

```bash
cd build
cmake ..
cmake --build .
```

### Run the program


**Windows**

```bash
cd Debug
scms
```

**Linux / Mac**

```bash
./scms
```

---

## Usage

1. Start the application.
2. Enter the institute name.
3. Choose Login or Exit.
4. Login with your credentials.
5. Access modules based on role.
6. All data is saved automatically.

---

## Design Overview

* `Person` is the base class
* `User` inherits from Person
* `Student`, `Teacher`, and `Admin` inherit from User
* Each subsystem is implemented as a separate module
* Authentication and role control are centralized
* Logger records system events and errors

---

## Logging

* Log file: `logs/scms.log`
* Supports:

  * INFO
  * WARNING
  * ERROR
* Logs system startup, login attempts, and module actions

---

## Security

* Passwords are stored using **hashing**
* Plain-text passwords are never saved
* Role-based access control is enforced

---

## Author

###### **[Bhomika Bhasin](https://github.com/bhomikabhasin001), [Heena Tariq](https://github.com/heenatariq765), [Priya Sharma](https://github.com/PriyaSharma050) and [Rohini Sarna](https://github.com/Rohinisarna146)**

B.Tech – Computer Science and Engineering
**GCET Jammu**

---

## License

This project is developed **for educational purposes only**.


