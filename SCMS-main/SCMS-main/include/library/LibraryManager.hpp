#pragma once
#include "../include/library/Book.hpp"
#include <vector>
#include <string>

using std::vector, std::string;

class LibraryManager {
private:
    vector<Book> books;
    string dataDir; // data/library/

public:
    LibraryManager() = default;
    LibraryManager(const string& dir);

    void addBook(const Book& book);
    void issueBook(const string& bookID);
    void returnBook(const string& bookID);

    void listBooks() const;
    void saveBooks();
    void loadBooks();
    void menu(); // full admin access
    void studentMenu(const string& studentUsername); // borrow/return books, view

};
