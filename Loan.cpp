#include "Loan.h"

/**************************** Loan Class ****************************/

// Constructor
// 반납 날짜는 반납 이전에는 비어있다.
Loan::Loan(Member* member, Book* book, string borrowDate)
	:m_member(member), m_book(book), m_borrowDate(borrowDate), m_returnDate("") {
}

// member getter
Member* Loan::getMember() const {
	return m_member;
}

// book getter
Book* Loan::getBook() const {
	return m_book;
}

// borrowDate getter
string Loan::getBorrowDate() const {
	return m_borrowDate;
}

// returnDate getter
string Loan::getReturnDate() const {
	return m_returnDate;
}

// returnDate setter
// 반납이 발생했을 경우 현재 날짜 기록
void Loan::setReturnDate(const string& returnDate) {
	this->m_returnDate = returnDate;
}