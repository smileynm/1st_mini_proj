#ifndef __MEMBER_H__
#define __MEMBER_H__
#include <iostream>
#include <vector>
#include "Book.h"
using namespace std;

class Member {
public:
	Member(string memberId, string name, string contact);
	string getMemberId() const;
	string getName() const;
	string getContact() const;
	const vector<Book*>& getBorrowedbooks() const;
	void borrowBook(Book* book);
	void returnBook(Book* book);
	bool isBorrowing(const Book* book) const;
private:
	string m_memberId;
	string m_name;
	string m_contact;
	vector<Book*> borrowedBooks;
};

#endif