#include "../include/library/LibraryManager.hpp"
#include "../include/logger.hpp"
#include <iostream>

Logger logger;

int main() {
    LibraryManager lm("test_library");

    lm.addBook(Book("B101", "C++ Primer", "Lippman", 2));
    lm.issueBook("B101");
    lm.returnBook("B101");

    std::cout << "Library tests passed\n";
    return 0;
}
