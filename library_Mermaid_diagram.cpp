classDiagram
    class LibrarySystem {
        -LibraryCatalog catalog
        -MemberManager memberManager
        -LoanManager loanManager
        +void run()
        +void displayMenu()
        +void processUserInput()
        +void handleAddBook()
        +void handleRegisterMember()
        +void handleBorrowBook()
        +void handleReturnBook()
        +void handleSearchBook()
        +void displayAllBooks()
        +void displayAllMembers()
        +void displayMemberLoans()
        +void displayAllLoans()
    }

    class LibraryCatalog {
        -map~string, Book*~ booksByISBN
        +~LibraryCatalog()
        +void addBook(string title, string author, string isbn, int quantity)
        +Book* findBookByISBN(string isbn)
        +vector~Book*~ searchBooks(string keyword)
        +void removeBook(string isbn)
        +void displayAllBooks()
    }

    class MemberManager {
        -map~string, Member*~ membersById
        +~MemberManager()
        +void registerMember(string memberId, string name, string contact)
        +Member* findMemberById(string memberId)
        +void removeMember(string memberId)
        +void displayAllMembers()
    }

    class LoanManager {
        -vector~Loan~ currentLoans
        +bool borrowBook(Member* member, Book* book)
        +bool returnBook(Member* member, Book* book)
        +void displayMemberLoans(const Member* member)
        +void displayAllLoans()
    }

    class Book {
        -string m_title
        -string m_author
        -string m_isbn
        -int m_quantity
        -bool isAvailable
        +Book(string title, string author, string isbn)
        +string getTitle() const
        +string getAuthor() const
        +string getISBN() const
        +bool getAvailability() const
        +void setAvailability(bool availability)
    }

    class Member {
        -string m_memberId
        -string m_name
        -string m_contact
        -vector~Book*~ borrowedBooks
        +Member(string memberId, string name, string contact)
        +string getMemberId() const
        +string getName() const
        +string getContact() const
        +const vector~Book*~& getBorrowedBooks() const
        +void borrowBook(Book* book)
        +void returnBook(Book* book)
        +bool isBorrowing(const Book* book) const
    }

    class Loan {
        -Member* member
        -Book* book
        -string borrowDate
        -string returnDate
        +Loan(Member* member, Book* book, string borrowDate)
        +Member* getMember() const
        +Book* getBook() const
        +string getBorrowDate() const
        +string getReturnDate() const
        +void setReturnDate(string returnDate)
    }

    class CsvDataManager {
        +static bool saveBooksToCsv(const LibraryCatalog& catalog, const std::string& filePath)
        +static bool loadBooksFromCsv(LibraryCatalog, const std::string& filePath)
        +static bool saveMembersToCsv(const MemberManager& memberManager, const std::string& filePath)
        +static bool loadMembersFromCsv(MemberManager& memberManager, const std::string& filePath)
    }

    CsvDataManager "1" o-- "*" Book : saves
    CsvDataManager "1" o-- "*" Member : saves

    LibrarySystem "1" *-- "1" LibraryCatalog : manages
    LibrarySystem "1" *-- "1" MemberManager : manages
    LibrarySystem "1" *-- "1" LoanManager : manages

    LibraryCatalog "1" o-- "*" Book : contains
    MemberManager "1" o-- "*" Member : contains
    LoanManager "1" o-- "*" Loan : manages

    Loan "1" -- "1" Member : relates to
    Loan "1" -- "1" Book : relates to

    Member "1" --> "*" Book : borrows (via borrowedBooks)
