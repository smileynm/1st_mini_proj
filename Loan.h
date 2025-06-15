#ifndef __LOAN_H__
#define __LOAN_H__
#include <iostream>
#include "Member.h"
#include "Book.h"
using namespace std;

class Loan {
public:
	Loan(Member* member, Book* book, string borrowDate);
	Member* getMember() const;
	Book* getBook() const;
	string getBorrowDate() const;
	string getReturnDate() const;
	void setReturnDate(const string& returnDate);

private:
	Member* m_member;
	Book* m_book;
	string m_borrowDate;
	string m_returnDate;
};

#endif