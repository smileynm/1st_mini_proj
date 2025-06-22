#define _CRT_SECURE_NO_WARNGINGS
#include "LoanManager.h"
#include "Member.h"
#include "Book.h"
#include "Loan.h"

#include <iostream>
#include <iomanip> // 날짜/시간 포맷
#include <sstream>
#include <ctime>
#include <cerrno>

// 대출 처리 메서드 구현
bool LoanManager::borrowBook(Member* member, Book* book) {
    // 유효성 검사: member와 book이 nullptr이 아닌지, 책이 대출 가능한 상태인지 확인
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

    // 대출일자 생성 (yyyy-MM-dd 형식)
    time_t t = time(nullptr);   // 현재 시간
    tm now; // tm 구조체 변수 선언 (포인터 아님)
    errno_t err = localtime_s(&now, &t); // <-- localtime_s 사용

    if (err != 0) {
        std::cerr << "Error getting local time for borrow date." << std::endl;
        return false; // 시간 정보 획득 실패 시 처리
    }

    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << now.tm_year + 1900 << "-" // now는 포인터가 아니므로 . 연산자 사용
        << std::setw(2) << std::setfill('0') << now.tm_mon + 1 << "-"
        << std::setw(2) << std::setfill('0') << now.tm_mday;
    std::string borrowDate = ss.str();

    // Loan 객체 생성
    Loan newLoan(member, book, borrowDate);

    // 대출 목록에 추가
    currentLoans.push_back(newLoan);

    // Book의 isAvailable 상태 변경
    book->setAvailability(false);

    // Member의 borrowedBooks 목록에 Book 추가
    member->borrowBook(book);

    std::cout << "Book borrowed: Member \"" << member->getName() << "\" (ID: " << member->getMemberId()
        << ") borrowed book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN()
        << ") on " << borrowDate << std::endl;
    return true;
}

// 반납 처리 메서드 구현
bool LoanManager::returnBook(Member* member, Book* book) {
    // 유효성 검사: member와 book이 nullptr이 아닌지, 책이 대출 중인지 확인
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

    // 반납일자 생성
    time_t t = time(nullptr);
    tm now; // tm 구조체 변수 선언
    errno_t err = localtime_s(&now, &t); // <-- localtime_s 사용

    if (err != 0) {
        std::cerr << "Error getting local time for return date." << std::endl;
        return false; // 시간 정보 획득 실패 시 처리
    }

    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << now.tm_year + 1900 << "-" // now는 포인터가 아니므로 . 연산자 사용
        << std::setw(2) << std::setfill('0') << now.tm_mon + 1 << "-"
        << std::setw(2) << std::setfill('0') << now.tm_mday;
    std::string returnDate = ss.str();

    // Loan 객체 찾기 (currentLoans에서 해당 대출 기록 찾기)
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

    // Loan 객체에 반납일자 설정
    loanToUpdate->setReturnDate(returnDate);

    // Book의 isAvailable 상태 변경
    book->setAvailability(true);

    // Member의 borrowedBooks 목록에서 Book 제거
    member->returnBook(book);

    std::cout << "Book returned: Member \"" << member->getName() << "\" (ID: " << member->getMemberId()
        << ") returned book \"" << book->getTitle() << "\" (ISBN: " << book->getISBN()
        << ") on " << returnDate << std::endl;
    return true;
}

// 특정 회원의 대출 목록 출력 메서드 구현
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

// 전체 대출 기록 출력 메서드 구현
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