#include "CsvDataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Book �����͸� CSV �������� ������
std::string CsvDataManager::formatBookToCsvLine(const Book& book) {
    std::stringstream ss;
    // CSV �ʵ� ����: ISBN, Title, Author, IsAvailable
    ss << book.getISBN() << ","
        << book.getTitle() << ","
        << book.getAuthor() << ","
        << (book.getAvailability() ? "true" : "false");
    return ss.str();
}

// Member �����͸� CSV �������� ������
std::string CsvDataManager::formatMemberToCsvLine(const Member& member) {
    std::stringstream ss;
    // CSV �ʵ� ����: MemberId, Name, Contact, BorrowedISBNs (�����ݷ����� ����)
    ss << member.getMemberId() << ","
        << member.getName() << ","
        << member.getContact() << ",";

    const auto& borrowedBooks = member.getBorrowedBooks();
    for (size_t i = 0; i < borrowedBooks.size(); ++i) {
        ss << borrowedBooks[i]->getISBN();
        if (i < borrowedBooks.size() - 1) {
            ss << ";";
        }
    }
    return ss.str();
}

// CSV ������ Book �����ͷ� �Ľ�
Book* CsvDataManager::parseBookFromCsvLine(const std::string& line) {
    std::stringstream ss(line);
    std::string isbn, title, author, availability_str;

    if (std::getline(ss, isbn, ',') &&
        std::getline(ss, title, ',') &&
        std::getline(ss, author, ',') &&
        std::getline(ss, availability_str)) {

        bool isAvailable = (availability_str == "true");
        Book* book = new Book(title, author, isbn);
        book->setAvailability(isAvailable);
        return book;
    }
    return nullptr;
}

// CSV ������ Member �����ͷ� �Ľ�
Member* CsvDataManager::parseMemberFromCsvLine(const std::string& line, LibraryCatalog& catalog) {
    std::stringstream ss(line);
    std::string memberId, name, contact, borrowed_isbns_str;

    if (std::getline(ss, memberId, ',') &&
        std::getline(ss, name, ',') &&
        std::getline(ss, contact, ',') &&
        std::getline(ss, borrowed_isbns_str)) {

        Member* member = new Member(memberId, name, contact);

        // ������ å ���� �Ľ� �� �߰�
        if (!borrowed_isbns_str.empty()) {
            std::stringstream borrowed_ss(borrowed_isbns_str);
            std::string isbn;
            while (std::getline(borrowed_ss, isbn, ';')) { // �����ݷ����� ���е� ISBN ���
                Book* book = catalog.findBookByISBN(isbn);
                if (book) {
                    member->borrowBook(book);
                    book->setAvailability(false); // å ���� ������Ʈ
                }
                else {
                    std::cerr << "Warning: Book with ISBN " << isbn << " borrowed by member "
                        << memberId << " not found in catalog." << std::endl;
                }
            }
        }
        return member;
    }
    return nullptr;
}

// å �����͸� CSV ���Ϸ� ����
bool CsvDataManager::saveBooksToCsv(const LibraryCatalog& catalog, const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return false;
    }

    std::vector<std::string> allISBNs = catalog.getAllISBNs();
    for (const std::string& isbn : allISBNs) {
        Book* book = catalog.findBookByISBN(isbn);
        if (book) {
            outFile << formatBookToCsvLine(*book) << std::endl;
        }
    }

    outFile.close();
    std::cout << "Books saved to CSV file: " << filePath << std::endl;
    return true;
}

// CSV ���Ͽ��� å ������ �ε�
bool CsvDataManager::loadBooksFromCsv(LibraryCatalog& catalog, const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Warning: Could not open file for reading: " << filePath << std::endl;
        return true; // ������ ��� �������� ó��
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        Book* book = parseBookFromCsvLine(line);
        if (book) {
            if (!catalog.findBookByISBN(book->getISBN())) {
                // �� å �߰�
                catalog.addBook(book->getTitle(), book->getAuthor(), book->getISBN());

                // �߰��� å�� ���� ����
                Book* addedBook = catalog.findBookByISBN(book->getISBN());
                if (addedBook) {
                    addedBook->setAvailability(book->getAvailability());
                }

                delete book; // �ӽ� ��ü ����
            }
            else {
                std::cerr << "Warning: Book with ISBN " << book->getISBN() << " already exists in catalog." << std::endl;
                delete book;
            }
        }
        else {
            std::cerr << "Error: Failed to parse book data: " << line << std::endl;
        }
    }

    inFile.close();
    std::cout << "Books loaded from CSV file: " << filePath << std::endl;
    return true;
}

// ȸ�� �����͸� CSV ���Ϸ� ����
bool CsvDataManager::saveMembersToCsv(const MemberManager& memberManager, const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return false;
    }

    std::vector<std::string> allMemberIds = memberManager.getAllMemberIds();
    for (const std::string& memberId : allMemberIds) {
        Member* member = memberManager.findMemberById(memberId);
        if (member) {
            outFile << formatMemberToCsvLine(*member) << std::endl;
        }
    }

    outFile.close();
    std::cout << "Members saved to CSV file: " << filePath << std::endl;
    return true;
}

// CSV ���Ͽ��� ȸ�� ������ �ε�
bool CsvDataManager::loadMembersFromCsv(MemberManager& memberManager, const std::string& filePath, LibraryCatalog& catalog) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Warning: Could not open file for reading: " << filePath << std::endl;
        return true; // ������ ��� �������� ó��
    }

    std::string line;
    while (std::getline(inFile, line)) {
        //if (line.empty()) continue;

        Member* member = parseMemberFromCsvLine(line, catalog);
        //if (!line.empty()) {
        //    if (!memberManager.findMemberById(member->getMemberId())) {
        //        // �� ȸ�� �߰� (���� ������ �߰�)
        //        memberManager.addMemberPointer(member);
        //    }
        //    else {
        //        std::cerr << "Warning: Member with ID " << member->getMemberId() << " already exists." << std::endl;
        //        delete member; // �ߺ��� ȸ���� �޸� ����
        //    }
        //}
        //else {
        //    std::cerr << "Error: Failed to parse member data: " << line << std::endl;
        //}
    }

    inFile.close();
    std::cout << "Members loaded from CSV file: " << filePath << std::endl;
    return true;
}