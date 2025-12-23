#include "../include/library/Book.hpp"
#include <stdexcept>
using namespace std;

Book::Book(const string& id, const string& t, const string& a, int c)
    : bookID(id), title(t), author(a), copies(c) {}

string Book::getID() const { return bookID; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getCopies() const { return copies; }

void Book::addCopies(int count) { copies += count; }

void Book::removeCopies(int count) {
    if (count > copies) throw runtime_error("No copies available");
    copies -= count;
}
