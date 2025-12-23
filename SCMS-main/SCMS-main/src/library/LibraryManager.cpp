#include "../include/library/LibraryManager.hpp"
#include "../include/logger.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

extern Logger logger;
namespace fs = filesystem;

LibraryManager::LibraryManager(const string& dir) : dataDir(dir) {
    fs::create_directories(dataDir);
    loadBooks();
}

void LibraryManager::addBook(const Book& book) {
    books.push_back(book);
    saveBooks();
    logger.log(LogLevel::INFO, "LIBRARY", "Added book: " + book.getTitle());
}

void LibraryManager::issueBook(const string& bookID) {
    auto it = find_if(books.begin(), books.end(), [&](const Book& b){ return b.getID() == bookID; });
    if (it == books.end()) throw runtime_error("Book not found");
    it->removeCopies(1);

    // Log transaction
    ofstream fout(fs::path(dataDir) / "transactions.log", ios::app);
    fout << "Issued: " << bookID << "\n";
    fout.close();

    saveBooks();
    logger.log(LogLevel::INFO, "LIBRARY", "Issued book: " + bookID);
}

void LibraryManager::returnBook(const string& bookID) {
    auto it = find_if(books.begin(), books.end(), [&](const Book& b){ return b.getID() == bookID; });
    if (it == books.end()) throw runtime_error("Book not found");
    it->addCopies(1);

    // Log transaction
    ofstream fout(fs::path(dataDir) / "transactions.log", ios::app);
    fout << "Returned: " << bookID << "\n";
    fout.close();

    saveBooks();
    logger.log(LogLevel::INFO, "LIBRARY", "Returned book: " + bookID);
}

void LibraryManager::listBooks() const {
    for (auto& b : books) {
        cout << b.getID() << " | " << b.getTitle() << " | " << b.getAuthor() 
                  << " | Copies: " << b.getCopies() << "\n";
    }
}

void LibraryManager::saveBooks() {
    ofstream fout(fs::path(dataDir) / "books.dat", ios::binary);
    for (auto& b : books) {
        fout << b.getID() << "\n" << b.getTitle() << "\n" << b.getAuthor() << "\n" << b.getCopies() << "\n";
    }
}

void LibraryManager::loadBooks() {
    books.clear();
    ifstream fin(fs::path(dataDir) / "books.dat", ios::binary);
    if (!fin) return;
    while (!fin.eof()) {
        string id, title, author;
        int copies;
        if (!getline(fin, id)) break;
        if (!getline(fin, title)) break;
        if (!getline(fin, author)) break;
        fin >> copies; fin.ignore();
        books.push_back(Book(id, title, author, copies));
    }
}

void LibraryManager::menu() {
    int choice;
    while (true) {
        cout << "\n--- Library Menu ---\n";
        cout << "1. List Books\n2. Add Book\n3. Issue Book\n4. Return Book\n5. Back\nChoice: ";

        if (!(cin >> choice)) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; 
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 5) break;

        string id, title, author;
        int copies;

        switch (choice) {
            case 1:
                listBooks();
                break;

            case 2: // Add Book
                cout << "Book ID: "; getline(cin, id);
                cout << "Title: "; getline(cin, title);
                cout << "Author: "; getline(cin, author);
                cout << "Copies: "; cin >> copies; cin.ignore();
                addBook(Book(id, title, author, copies));
                logger.log(LogLevel::INFO, "LIBRARY", "Added book: " + id);
                break;

            case 3: // Issue Book
                cout << "Book ID to issue: "; getline(cin, id);
                try {
                    issueBook(id);
                    logger.log(LogLevel::INFO, "LIBRARY", "Issued book: " + id);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                    logger.log(LogLevel::ERROR, "LIBRARY", e.what());
                }
                break;

            case 4: // Return Book
                cout << "Book ID to return: "; getline(cin, id);
                try {
                    returnBook(id);
                    logger.log(LogLevel::INFO, "LIBRARY", "Returned book: " + id);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                    logger.log(LogLevel::ERROR, "LIBRARY", e.what());
                }
                break;

            default:
                cout << "Invalid choice!\n";
                logger.log(LogLevel::WARNING, "LIBRARY", "Invalid menu choice");
        }
    }
}

void LibraryManager::studentMenu(const string& studentUsername) {
    int choice;
    while (true) {
        cout << "\n--- Library Services ---\n";
        cout << "1. List Books\n2. Borrow Book\n3. Return Book\n4. Back\nChoice: ";

        if (!(cin >> choice)) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; 
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 4) break;

        string id;
        switch (choice) {
            case 1: // List Books
                listBooks();
                break;

            case 2: // Borrow Book
                cout << "Enter Book ID to borrow: ";
                getline(cin, id);
                try {
                    issueBook(id); // Reduce available copies
                    logger.log(LogLevel::INFO, "LIBRARY", studentUsername + " borrowed book: " + id);
                    cout << "Book borrowed successfully.\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                    logger.log(LogLevel::ERROR, "LIBRARY", e.what());
                }
                break;

            case 3: // Return Book
                cout << "Enter Book ID to return: ";
                getline(cin, id);
                try {
                    returnBook(id); // Increase available copies
                    logger.log(LogLevel::INFO, "LIBRARY", studentUsername + " returned book: " + id);
                    cout << "Book returned successfully.\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                    logger.log(LogLevel::ERROR, "LIBRARY", e.what());
                }
                break;

            default:
                cout << "Invalid choice!\n";
                logger.log(LogLevel::WARNING, "LIBRARY", "Invalid student menu choice");
        }
    }
}
