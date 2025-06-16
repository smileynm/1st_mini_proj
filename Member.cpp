#include "Member.h"

/**************************** Member Class ****************************/

// Constructor
Member::Member(string memberId, string name, string contact)
	: m_memberId(memberId), m_name(name), m_contact(contact) {
}

// memberID getter
string Member::getMemberId() const {
	return m_memberId;
}

// memberName getter
string Member::getName() const {
	return m_name;
}

// phoneNumber getter
string Member::getContact() const {
	return m_contact;
}

// borrowedBooks getter
// 현재 대여중인 책들을 따로 vector로 관리하여 list-up
const vector<Book*>& Member::getBorrowedBooks() const {
	return borrowedBooks;
}

// borrowBook 함수
void Member::borrowBook(Book* book) {
	borrowedBooks.push_back(book);	// 빌린 책 vector의 뒤에 빌리려는 책 추가
}

// 반납 시퀀스
void Member::returnBook(Book* book) {
	bool flag = 0; // 예외처리용 플래그
	for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) { // begin부터 end까지 탐색
		if (*it == book) {
			borrowedBooks.erase(it);
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		printf("대여중인 책이 아닙니다\n");
}

// 대여중인지 확인하는 함수
bool Member::isBorrowing(const Book* book) const {
	return book->getAvailability();
}