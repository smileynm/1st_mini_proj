#include "Loan.h"

/**************************** Loan Class ****************************/

// Constructor
// �ݳ� ��¥�� �ݳ� �������� ����ִ�.
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
// �ݳ��� �߻����� ��� ���� ��¥ ���
void Loan::setReturnDate(const string& returnDate) {
	this->m_returnDate = returnDate;
}