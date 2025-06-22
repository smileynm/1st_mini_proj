#pragma once
#include "Book.h"
/**************************** Book Class ****************************/

// Constructor
Book::Book(string title, string author, string isbn)
	: m_title(title), m_author(author), m_isbn(isbn) {
	m_isAvailable = true;
}

// title getter
string Book::getTitle() const {
	return m_title;
}

// author getter
string Book::getAuthor() const {
	return m_author;
}

// isbn getter
string Book::getISBN() const {
	return m_isbn;
}

// availability getter
// 대여 가능 여부
bool Book::getAvailability() const {
	return m_isAvailable;
}

// availability setter
// 대출시 0, 반납시 1
void Book::setAvailability(bool availability) {
	m_isAvailable = availability;
}