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
// catalog�� �Ҹ�� ��, �ʿ� ����� ��� Book ��ü�� �޸� ����
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
	// �̹� �ִ� å�� �߰��Ϸ��� �ϸ� false
	if (booksByISBN.count(isbn)) {
		cerr << "Error: Book with ISBN" << isbn << " already exists." << endl;
		return false;
	}
	
	// ���ο� ��ü�� �������� ����
	Book* newBook = new Book(title, author, isbn);
	// �ʿ� ���ο� ��ü �߰�
	booksByISBN[isbn] = newBook;
	cout << "Book added: " << title << " (" << isbn << ")" << endl;
	return true;
}

// ISBN�� Ȱ���� å �˻� �޼��� ����
Book* LibraryCatalog::findBookByISBN(const string& isbn) const {
	auto it = booksByISBN.find(isbn);
	if (it != booksByISBN.end()) {
		// ã�� ��� Book* ������ ��ȯ
		return it->second;
	}
	// �� ã�� ��� nullptr ��ȯ
	return nullptr;
}

vector<Book*> LibraryCatalog::searchBooks(const string& keyword) const {
	vector<Book*> results;
	if (keyword.empty()) { // Ű���尡 ���� ���
		// ��� å ��ȯ
		for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
			string isbn = it->first;
			Book* book_ptr = it->second;
			results.push_back(book_ptr);
		}
		return results;
	}
	// �˻���� ���� ���ڿ��� ��� �ҹ��ڷ� ��ȯ (�� ���̼��� ����)
	string lowerKeyword = toLower(keyword);

	for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
		Book* book_ptr = it->second;
		
		string lowerTitle = toLower(book_ptr->getTitle());
		string lowerAuthor = toLower(book_ptr->getAuthor());

		// ���� �Ǵ� ���ڿ� Ű���� ���ڿ��� ���ԵǾ� �ִ��� Ȯ��
		if (lowerTitle.find(lowerKeyword) != std::string::npos ||
			lowerAuthor.find(lowerKeyword) != std::string::npos) {
			results.push_back(book_ptr); // ��� ��Ͽ� �߰�
		}
	}
	return results;	// �˻� ��� vector ��ȯ
}

// å ���� �޼��� ����
bool LibraryCatalog::removeBook(const std::string& isbn) {
	// �ʿ��� ISBN���� å ã��
	auto it = booksByISBN.find(isbn);
	if (it == booksByISBN.end()) {
		std::cerr << "Error: Book with ISBN " << isbn << " not found for removal." << std::endl;
		return false; // å�� ������ ���� ����
	}

	// ã�� Book ��ü�� �޸� ����
	delete it->second;

	// �ʿ��� �ش� �׸� ����
	booksByISBN.erase(it);
	std::cout << "Book removed: " << isbn << std::endl;
	return true; // ���� ����
}

// ��� å ���� ��� �޼��� ����
void LibraryCatalog::displayAllBooks() const {
	if (booksByISBN.empty()) {
		std::cout << "The library catalog is empty." << std::endl;
		return;
	}

	std::cout << "\n--- Library Catalog ---" << std::endl;
	// ���� Ű(ISBN) ������ ���ĵǾ� ��ȸ�˴ϴ�.
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

// ��� ISBN ��� ��ȯ �޼��� ����
std::vector<std::string> LibraryCatalog::getAllISBNs() const {
	std::vector<std::string> isbns;
	isbns.reserve(booksByISBN.size()); // �̸� ũ�⸦ �����Ͽ� ȿ���� ���

	for (auto it = booksByISBN.begin(); it != booksByISBN.end(); ++it) {
		string isbn = it->first;
		isbns.push_back(isbn);
	}
	return isbns;
}


// ���ڿ� �ҹ��� ��ȯ ���� �Լ� ����
std::string LibraryCatalog::toLower(const std::string& str) {
	std::string lower_str = str;
	std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
		[](unsigned char c) { return std::tolower(c); }); // �� ���ڸ� �ҹ��ڷ� ��ȯ
	return lower_str;
}
