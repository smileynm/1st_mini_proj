#define _CRT_SECURE_NO_WARNGINGS
#include "LoanManager.h"
#include "Member.h"
#include "Book.h"
#include "Loan.h"

#include <iostream>
#include <iomanip> // ��¥/�ð� ����
#include <sstream>
#include <ctime>
#include <cerrno>

// ���� ó�� �޼��� ����
bool LoanManager::borrowBook(Member* member, Book* book) {
    // ��ȿ�� �˻�: member�� book�� nullptr�� �ƴ���, å�� ���� ������ �������� Ȯ��
    if (!member || !book) {
        std::cerr << "Error: Invalid member or book." << std::endl;
        return false;
    }
    if (!book->getAvailability()) {
        std::cerr << "Error: Book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN() << ") is not available." << std::endl;
        return false;
    }
    if (member->isBorrowing(book)=='true') {
        std::cerr << "Error: Member \"" << member->getName() << "\" (ID: " << member->getMemberId()
            << ") is already borrowing book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN() << ")." << std::endl;
        return false;
    }

    // �������� ���� (yyyy-MM-dd ����)
    time_t t = time(nullptr);   // ���� �ð�
    tm now; // tm ����ü ���� ���� (������ �ƴ�)
    errno_t err = localtime_s(&now, &t); // <-- localtime_s ���

    if (err != 0) {
        std::cerr << "Error getting local time for borrow date." << std::endl;
        return false; // �ð� ���� ȹ�� ���� �� ó��
    }

    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << now.tm_year + 1900 << "-" // now�� �����Ͱ� �ƴϹǷ� . ������ ���
        << std::setw(2) << std::setfill('0') << now.tm_mon + 1 << "-"
        << std::setw(2) << std::setfill('0') << now.tm_mday;
    std::string borrowDate = ss.str();

    // Loan ��ü ����
    Loan newLoan(member, book, borrowDate);

    // ���� ��Ͽ� �߰�
    currentLoans.push_back(newLoan);

    // Book�� isAvailable ���� ����
    book->setAvailability(false);

    // Member�� borrowedBooks ��Ͽ� Book �߰�
    member->borrowBook(book);

    std::cout << "Book borrowed: Member \"" << member->getName() << "\" (ID: " << member->getMemberId()
        << ") borrowed book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN()
        << ") on " << borrowDate << std::endl;
    return true;
}

// �ݳ� ó�� �޼��� ����
bool LoanManager::returnBook(Member* member, Book* book) {
    // ��ȿ�� �˻�: member�� book�� nullptr�� �ƴ���, å�� ���� ������ Ȯ��
    if (!member || !book) {
        std::cerr << "Error: Invalid member or book." << std::endl;
        return false;
    }
    if (book->getAvailability()) {
        std::cerr << "Error: Book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN() << ") is not currently borrowed." << std::endl;
        return false;
    }
    if (!member->isBorrowing(book)) {
        std::cerr << "Error: Member \"" << member->getName() << "\" (ID: " << member->getMemberId()
            << ") has not borrowed book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN() << ")." << std::endl;
        return false;
    }

    // �ݳ����� ����
    time_t t = time(nullptr);
    tm now; // tm ����ü ���� ����
    errno_t err = localtime_s(&now, &t); // <-- localtime_s ���

    if (err != 0) {
        std::cerr << "Error getting local time for return date." << std::endl;
        return false; // �ð� ���� ȹ�� ���� �� ó��
    }

    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << now.tm_year + 1900 << "-" // now�� �����Ͱ� �ƴϹǷ� . ������ ���
        << std::setw(2) << std::setfill('0') << now.tm_mon + 1 << "-"
        << std::setw(2) << std::setfill('0') << now.tm_mday;
    std::string returnDate = ss.str();

    // Loan ��ü ã�� (currentLoans���� �ش� ���� ��� ã��)
    Loan* loanToUpdate = nullptr;
    for (Loan& loan : currentLoans) {
        if (loan.getMember() == member && loan.getBook() == book) {
            loanToUpdate = &loan;
            break;
        }
    }

    if (!loanToUpdate) {
        std::cerr << "Error: Loan record not found for member \"" << member->getName()
            << "\" and book \"" << book->getTitle() << "\"." << std::endl;
        return false;
    }

    // Loan ��ü�� �ݳ����� ����
    loanToUpdate->setReturnDate(returnDate);

    // Book�� isAvailable ���� ����
    book->setAvailability(true);

    // Member�� borrowedBooks ��Ͽ��� Book ����
    member->returnBook(book);

    std::cout << "Book returned: Member \"" << member->getName() << "\" (ID: " << member->getMemberId()
        << ") returned book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN()
        << ") on " << returnDate << std::endl;
    return true;
}

// Ư�� ȸ���� ���� ��� ��� �޼��� ����
void LoanManager::displayMemberLoans(const Member* member) const {
    if (!member) {
        std::cerr << "Error: Invalid member." << std::endl;
        return;
    }

    std::cout << "\n--- Loans for Member: " << member->getName() << " (ID: " << member->getMemberId() << ") ---" << std::endl;
    bool found = false;
    for (const Loan& loan : currentLoans) {
        if (loan.getMember() == member) {
            std::cout << "  Book: \"" << loan.getBook()->getTitle() << "\" (ISBN: " << loan.getBook()->getISBN()
                << "), Borrowed on: " << loan.getBorrowDate()
                << ", Returned on: " << (loan.getReturnDate().empty() ? "Not yet returned" : loan.getReturnDate())
                << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No loans found for this member." << std::endl;
    }
    std::cout << "------------------------------------------------------" << std::endl;
}

// ��ü ���� ��� ��� �޼��� ����
void LoanManager::displayAllLoans() const {
    if (currentLoans.empty()) {
        std::cout << "No loans recorded." << std::endl;
        return;
    }

    std::cout << "\n--- All Loans ---" << std::endl;
    for (const Loan& loan : currentLoans) {
        std::cout << "  Member: \"" << loan.getMember()->getName() << "\" (ID: " << loan.getMember()->getMemberId()
            << "), Book: \"" << loan.getBook()->getTitle() << "\" (ISBN: " << loan.getBook()->getISBN()
            << "), Borrowed on: " << loan.getBorrowDate()
            << ", Returned on: " << (loan.getReturnDate().empty() ? "Not yet returned" : loan.getReturnDate())
            << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}