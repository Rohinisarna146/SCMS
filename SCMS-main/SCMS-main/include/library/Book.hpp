#pragma once
#include <string>

using std::string;

class Book {
private:
    string bookID;
    string title;
    string author;
    int copies;

public:
    Book() = default;
    Book(const string& id, const string& t, const string& a, int c);

    string getID() const;
    string getTitle() const;
    string getAuthor() const;
    int getCopies() const;

    void addCopies(int count);
    void removeCopies(int count); // throws exception if not enough copies
};
