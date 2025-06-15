#include "LibraryCatalog.h"
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdexcept>

LibraryCatalog::LibraryCatalog() {
	cout << "LibraryCatalog created." << endl;
}

LibraryCatalog::~LibraryCatalog() {
	cout << "LibraryCatalog destroying..." << endl;
	for (auto const& [isbn, book_ptr] : booksByISBN) {
		cout << "Deleting book: " << book_ptr->getTitle() << " (" << isbn << ")" << endl;
		delete book_ptr;
	}
	booksByISBN.clear();
	cout << "LibraryCatalog destroyed." << endl;
}

bool LibraryCatalog::addBook(const string& title, const string& author, const string& isbn) {
	if (booksByISBN.count(isbn)) {
		cerr << "Error: Book with ISBN" << isbn << " already exists." << endl;
		return false;
	}
}