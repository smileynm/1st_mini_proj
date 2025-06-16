#pragma once
#ifndef __BOOK_H__
#define __BOOK_H__
#include <iostream>
using namespace std;

class Book {
public:
	Book(string title, string author, string isbn);
	string getTitle() const;
	string getAuthor() const;
	string getISBN() const;
	bool getAvailability() const;
	void setAvailability(bool availability);

private:
	string m_title;
	string m_author;
	string m_isbn;
	bool m_isAvailable;
};

#endif