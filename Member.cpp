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
// ���� �뿩���� å���� ���� vector�� �����Ͽ� list-up
const vector<Book*>& Member::getBorrowedBooks() const {
	return borrowedBooks;
}

// borrowBook �Լ�
void Member::borrowBook(Book* book) {
	borrowedBooks.push_back(book);	// ���� å vector�� �ڿ� �������� å �߰�
}

// �ݳ� ������
void Member::returnBook(Book* book) {
	bool flag = 0; // ����ó���� �÷���
	for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) { // begin���� end���� Ž��
		if (*it == book) {
			borrowedBooks.erase(it);
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		printf("�뿩���� å�� �ƴմϴ�\n");
}

// �뿩������ Ȯ���ϴ� �Լ�
bool Member::isBorrowing(const Book* book) const {
	return book->getAvailability();
}