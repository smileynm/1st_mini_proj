#ifndef __LIBRARY_CATALOG_H__
#define __LIBRARY_CATALOG_H__
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Book.h"
using namespace std;

class LibraryCatalog {
public:
	LibraryCatalog();
	~LibraryCatalog();
	LibraryCatalog(const LibraryCatalog&) = delete;
	LibraryCatalog& operator = (const LibraryCatalog&) = delete;
	// 복사 생성자 및 대입 연산자 방지

	bool addBook(const string& title, const string& author, const string& isbn);
	Book* findBookByISBN(const string& isbn) const;
	vector<Book*> searchBooks(const string& keyword) const;
	bool removeBook(const string& isbn);
	void displayAllBooks() const;
	vector<string> getAllISBNs() const;

private:
	map<string, Book*> booksByISBN;
	static string toLower(const string& str);
};

#endif	// __LIBRARY_CATALOG_H__