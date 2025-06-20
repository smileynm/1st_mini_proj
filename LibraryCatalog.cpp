#include "LibraryCatalog.h"
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdexcept>

// Constructor
LibraryCatalog::LibraryCatalog() {
	cout << "LibraryCatalog created." << endl;
}

// Destroyer
// catalog가 소멸될 때, 맵에 저장된 모든 Book 객체의 메모리 해제
LibraryCatalog::~LibraryCatalog() {
	cout << "LibraryCatalog destroying..." << endl;
	for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
		string isbn = it->first;
		Book* book_ptr = it->second;
		cout << "Deleting book: " << book_ptr->getTitle() << " (" << isbn << ")" << endl;
		delete book_ptr;
	}
	booksByISBN.clear();
	cout << "LibraryCatalog destroyed." << endl;
}

// 
bool LibraryCatalog::addBook(const string& title, const string& author, const string& isbn) {
	// 이미 있는 책을 추가하려고 하면 false
	if (booksByISBN.count(isbn)) {
		cerr << "Error: Book with ISBN" << isbn << " already exists." << endl;
		return false;
	}
	
	// 새로운 객체를 동적으로 생성
	Book* newBook = new Book(title, author, isbn);
	// 맵에 새로운 객체 추가
	booksByISBN[isbn] = newBook;
	cout << "Book added: " << title << " (" << isbn << ")" << endl;
	return true;
}

// ISBN을 활용한 책 검색 메서드 구현
Book* LibraryCatalog::findBookByISBN(const string& isbn) const {
	auto it = booksByISBN.find(isbn);
	if (it != booksByISBN.end()) {
		// 찾은 경우 Book* 포인터 반환
		return it->second;
	}
	// 못 찾은 경우 nullptr 반환
	return nullptr;
}

vector<Book*> LibraryCatalog::searchBooks(const string& keyword) const {
	vector<Book*> results;
	if (keyword.empty()) { // 키워드가 없을 경우
		// 모든 책 반환
		for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
			string isbn = it->first;
			Book* book_ptr = it->second;
			results.push_back(book_ptr);
		}
		return results;
	}
	// 검색어와 비교할 문자열을 모두 소문자로 변환 (비교 용이성을 위해)
	string lowerKeyword = toLower(keyword);

	for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
		Book* book_ptr = it->second;
		
		string lowerTitle = toLower(book_ptr->getTitle());
		string lowerAuthor = toLower(book_ptr->getAuthor());

		// 제목 또는 저자에 키워드 문자열이 포함되어 있는지 확인
		if (lowerTitle.find(lowerKeyword) != std::string::npos ||
			lowerAuthor.find(lowerKeyword) != std::string::npos) {
			results.push_back(book_ptr); // 결과 목록에 추가
		}
	}
	return results;	// 검색 결과 vector 반환
}

// 책 제거 메서드 구현
bool LibraryCatalog::removeBook(const std::string& isbn) {
	// 맵에서 ISBN으로 책 찾기
	auto it = booksByISBN.find(isbn);
	if (it == booksByISBN.end()) {
		std::cerr << "Error: Book with ISBN " << isbn << " not found for removal." << std::endl;
		return false; // 책이 없으면 제거 실패
	}

	// 찾은 Book 객체의 메모리 해제
	delete it->second;

	// 맵에서 해당 항목 제거
	booksByISBN.erase(it);
	std::cout << "Book removed: " << isbn << std::endl;
	return true; // 제거 성공
}

// 모든 책 정보 출력 메서드 구현
void LibraryCatalog::displayAllBooks() const {
	if (booksByISBN.empty()) {
		std::cout << "The library catalog is empty." << std::endl;
		return;
	}

	std::cout << "\n--- Library Catalog ---" << std::endl;
	// 맵은 키(ISBN) 순서로 정렬되어 순회
	for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
		string isbn = it->first;
		Book* book_ptr = it->second;
		std::cout << "  ISBN: " << isbn
			<< ", Title: \"" << book_ptr->getTitle() << "\""
			<< ", Author: " << book_ptr->getAuthor()
			<< ", Available: " << (book_ptr->getAvailability() ? "Yes" : "No")
			<< std::endl;
	}
	std::cout << "-----------------------" << std::endl;
}

// 모든 ISBN 목록 반환 메서드 구현
std::vector<std::string> LibraryCatalog::getAllISBNs() const {
	std::vector<std::string> isbns;
	isbns.reserve(booksByISBN.size()); // 미리 크기를 예약하여 효율성 향상

	for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
		string isbn = it->first;
		isbns.push_back(isbn);
	}
	return isbns;
}


// 문자열 소문자 변환 헬퍼 함수 구현
std::string LibraryCatalog::toLower(const std::string& str) {
	std::string lower_str = str;
	std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
		[](unsigned char c) { return std::tolower(c); }); // 각 문자를 소문자로 변환
	return lower_str;
}
