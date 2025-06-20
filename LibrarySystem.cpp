#include "LibrarySystem.h"
#include "CsvDataManager.h" // CsvDataManager 사용을 위해 포함
#include <limits> // std::numeric_limits
#include <ios>    // std::streamsize

// 생성자
LibrarySystem::LibrarySystem() {
    std::cout << "Library System initialized." << std::endl;
    // 관리자 객체들은 멤버 변수로 선언되었으므로 LibrarySystem 객체 생성 시 자동으로 생성
    // 여기서 초기 데이터 로딩을 할 수도 있다. (main에서 하거나 여기서 하거나 선택 가능)
}

// 소멸자
LibrarySystem::~LibrarySystem() {
    std::cout << "Library System shutting down." << std::endl;
    // 관리자 객체들은 LibrarySystem 객체 소멸 시 자동으로 소멸.
    // 여기서 최종 데이터 저장을 할 수도 있음음 (main에서 하거나 여기서 하거나 선택 가능)
}

// Getter 메서드 구현
LibraryCatalog& LibrarySystem::getCatalog() {
    return catalog;
}

MemberManager& LibrarySystem::getMemberManager() {
    return memberManager;
}

LoanManager& LibrarySystem::getLoanManager() {
    return loanManager;
}


// 시스템 메인 실행 루프
void LibrarySystem::run() {
    int choice = 0;
    while (choice != 11) { // 11번 메뉴가 종료라고 가정
        displayMenu();
        processUserInput();
        std::cout << "Enter your choice: ";
        if (std::cin >> choice) {
            // 입력 버퍼 비우기 (다음 getline 사용을 위해 필수)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
            case 1: handleAddBook(); break;
            case 2: handleRegisterMember(); break;
            case 3: handleBorrowBook(); break;
            case 4: handleReturnBook(); break;
            case 5: handleSearchBook(); break;
            case 6: handleDisplayAllBooks(); break;
            case 7: handleDisplayAllMembers(); break;
            case 8: handleDisplayMemberLoans(); break;
            case 9: handleDisplayAllLoans(); break;
            case 10: // 데이터 저장 기능 (종료 시 자동 저장 가능?)
                CsvDataManager::saveBooksToCsv(catalog, "books.csv");
                CsvDataManager::saveMembersToCsv(memberManager, "members.csv");
                std::cout << "Data saved manually." << std::endl;
                break;
            case 11: handleExit(); break; // 종료
            default: std::cout << "Invalid choice. Please try again." << std::endl; break;
            }
        }
        else {
            // 잘못된 입력 처리 (숫자가 아닌 문자 등)
            std::cerr << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // 오류 상태 플래그 초기화
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기
        }
    }
}

// 메뉴 출력
void LibrarySystem::displayMenu() {
    std::cout << "\n--- Library Management System Menu ---" << std::endl;
    std::cout << "1. Add Book" << std::endl;
    std::cout << "2. Register Member" << std::endl;
    std::cout << "3. Borrow Book" << std::endl;
    std::cout << "4. Return Book" << std::endl;
    std::cout << "5. Search Books" << std::endl;
    std::cout << "6. Display All Books" << std::endl;
    std::cout << "7. Display All Members" << std::endl;
    std::cout << "8. Display Member Loans" << std::endl;
    std::cout << "9. Display All Loans" << std::endl;
    std::cout << "10. Save Data (Manual)" << std::endl; // 수동 저장 옵션
    std::cout << "11. Exit" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}


// 각 기능 핸들러 메서드 구현 (스케치)
void LibrarySystem::handleAddBook() {
    std::string title, author, isbn;
    std::cout << "Enter Book Title: ";
    std::getline(std::cin, title);
    std::cout << "Enter Book Author: ";
    std::getline(std::cin, author);
    std::cout << "Enter Book ISBN: ";
    std::getline(std::cin, isbn);

    catalog.addBook(title, author, isbn);
}

void LibrarySystem::handleRegisterMember() {
    std::string memberId, name, contact;
    std::cout << "Enter Member ID: ";
    std::getline(std::cin, memberId);
    std::cout << "Enter Member Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Member Contact: ";
    std::getline(std::cin, contact);

    memberManager.registerMember(memberId, name, contact);
}

void LibrarySystem::handleBorrowBook() {
    std::string memberId, isbn;
    std::cout << "Enter Member ID: ";
    std::getline(std::cin, memberId);
    std::cout << "Enter Book ISBN: ";
    std::getline(std::cin, isbn);

    Member* member = memberManager.findMemberById(memberId);
    Book* book = catalog.findBookByISBN(isbn);

    loanManager.borrowBook(member, book);
}

void LibrarySystem::handleReturnBook() {
    std::string memberId, isbn;
    std::cout << "Enter Member ID: ";
    std::getline(std::cin, memberId);
    std::cout << "Enter Book ISBN: ";
    std::getline(std::cin, isbn);

    Member* member = memberManager.findMemberById(memberId);
    Book* book = catalog.findBookByISBN(isbn);

    loanManager.returnBook(member, book);
}

void LibrarySystem::handleSearchBook() {
    std::string keyword;
    std::cout << "Enter search keyword (Title or Author): ";
    std::getline(std::cin, keyword);

    std::vector<Book*> results = catalog.searchBooks(keyword);

    if (results.empty()) {
        std::cout << "No books found matching the keyword." << std::endl;
    }
    else {
        std::cout << "\n--- Search Results ---" << std::endl;
        for (const auto& book : results) {
            std::cout << "  ISBN: " << book->getISBN()
                << ", Title: \"" << book->getTitle() << "\""
                << ", Author: " << book->getAuthor()
                << ", Available: " << (book->getAvailability() ? "Yes" : "No")
                << std::endl;
        }
        std::cout << "----------------------" << std::endl;
    }
}

void LibrarySystem::handleDisplayAllBooks() {
    catalog.displayAllBooks();
}

void LibrarySystem::handleDisplayAllMembers() {
    memberManager.displayAllMembers();
}

void LibrarySystem::handleDisplayMemberLoans() {
    std::string memberId;
    std::cout << "Enter Member ID: ";
    std::getline(std::cin, memberId);

    Member* member = memberManager.findMemberById(memberId);
    if (member) {
        loanManager.displayMemberLoans(member);
    }
    else {
        std::cerr << "Error: Member with ID " << memberId << " not found." << std::endl;
    }
}

void LibrarySystem::handleDisplayAllLoans() {
    loanManager.displayAllLoans();
}

void LibrarySystem::handleExit() {
    std::cout << "Exiting Library Management System." << std::endl;
    // run 함수의 while 루프 조건(choice != 11)에 의해 종료
    // 여기서 추가적인 정리 작업이 필요하다면 수행할 수 있다.
}
