#include "LibrarySystem.h"
#include "CsvDataManager.h" // CsvDataManager ����� ���� ����
#include <limits> // std::numeric_limits
#include <ios>    // std::streamsize

// ������
LibrarySystem::LibrarySystem() {
    std::cout << "Library System initialized." << std::endl;
    // ������ ��ü���� ��� ������ ����Ǿ����Ƿ� LibrarySystem ��ü ���� �� �ڵ����� �����˴ϴ�.
    // ���⼭ �ʱ� ������ �ε��� �� ���� �ֽ��ϴ�. (main���� �ϰų� ���⼭ �ϰų� ���� ����)
}

// �Ҹ���
LibrarySystem::~LibrarySystem() {
    std::cout << "Library System shutting down." << std::endl;
    // ������ ��ü���� LibrarySystem ��ü �Ҹ� �� �ڵ����� �Ҹ�˴ϴ�.
    // ���⼭ ���� ������ ������ �� ���� �ֽ��ϴ�. (main���� �ϰų� ���⼭ �ϰų� ���� ����)
}

// Getter �޼��� ����
LibraryCatalog& LibrarySystem::getCatalog() {
    return catalog;
}

MemberManager& LibrarySystem::getMemberManager() {
    return memberManager;
}

LoanManager& LibrarySystem::getLoanManager() {
    return loanManager;
}


// �ý��� ���� ���� ����
void LibrarySystem::run() {
    int choice = 0;
    while (choice != 11) { // 11�� �޴��� ������ ����
        displayMenu();
        processUserInput();
        // processUserInput ���ο��� choice ���� ������Ʈ�ϰ� �ش� handle �Լ� ȣ��
        // �Ǵ� run �Լ� ������ ���� ����� �Է��� �ް� switch �� ������ �б�
        // ���⼭�� processUserInput�� �Է��� �ް� ������ handle �Լ��� ȣ���Ѵٰ� ����
        // ���� ���������� run �Լ� ������ �Է� ������ ������ ���� �� �Ϲ����Դϴ�.

        // ����: run �Լ� ������ �Է� ������ ������ ���
        std::cout << "Enter your choice: ";
        if (std::cin >> choice) {
            // �Է� ���� ���� (���� getline ����� ���� �ʼ�)
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
            case 10: // ������ ���� ��� (���� ����, ���� �� �ڵ� ���嵵 ����)
                CsvDataManager::saveBooksToCsv(catalog, "books.csv");
                CsvDataManager::saveMembersToCsv(memberManager, "members.csv");
                std::cout << "Data saved manually." << std::endl;
                break;
            case 11: handleExit(); break; // ����
            default: std::cout << "Invalid choice. Please try again." << std::endl; break;
            }
        }
        else {
            // �߸��� �Է� ó�� (���ڰ� �ƴ� ���� ��)
            std::cerr << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // ���� ���� �÷��� �ʱ�ȭ
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �Է� ���� ����
        }
    }
}

// �޴� ��� (����)
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
    std::cout << "10. Save Data (Manual)" << std::endl; // ���� ���� �ɼ�
    std::cout << "11. Exit" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

// ����� �Է� ó�� (run �Լ� ������ ���� ó���ϴ� ������� ����)
void LibrarySystem::processUserInput() {
    // �� �Լ��� ���� run �Լ� ������ ���� �Է� ó���� �ϹǷ� �ʿ� ���� �� �ֽ��ϴ�.
    // ���� ������ �Է� ��ȿ�� �˻� ���� �и��ϰ� �ʹٸ� ����� �� �ֽ��ϴ�.
}

// �� ��� �ڵ鷯 �޼��� ���� (����ġ)
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
    // run �Լ��� while ���� ����(choice != 11)�� ���� ����˴ϴ�.
    // ���⼭ �߰����� ���� �۾��� �ʿ��ϴٸ� ������ �� �ֽ��ϴ�.
}
