classDiagram
    class LibrarySystem {
        -LibraryCatalog catalog
        -MemberManager memberManager
        -LoanManager loanManager
        +LibrarySystem()
        +~LibrarySystem()
        +void run()
        +LibraryCatalog& getCatalog()
        +MemberManager& getMemberManager()
        +LoanManager& getLoanManager()
        -void displayMenu()
        -void processUserInput()
        -void handleAddBook()
        -void handleRegisterMember()
        -void handleBorrowBook()
        -void handleReturnBook()
        -void handleSearchBook()
        -void handleDisplayAllBooks()
        -void handleDisplayAllMembers()
        -void handleDisplayMemberLoans()
        -void handleDisplayAllLoans()
        -void handleExit()
    }

    class LibraryCatalog {
        -map~string, Book*~ booksByISBN
        +LibraryCatalog()
        +~LibraryCatalog()
        +bool addBook(string, string, string)
        +Book* findBookByISBN(string) const
        +vector~Book*~ searchBooks(string) const
        +bool removeBook(string)
        +void displayAllBooks() const
        +vector~string~ getAllISBNs() const
        -static string toLower(string)
    }

    class MemberManager {
        -map~string, Member*~ membersById
        +MemberManager()
        +~MemberManager()
        +bool registerMember(string, string, string)
        +Member* findMemberById(string) const
        +bool removeMember(string)
        +void displayAllMembers() const
        +vector~string~ getAllMemberIds() const
        +void addMemberPointer(Member*)
    }

    class LoanManager {
        -vector~Loan~ currentLoans
        +bool borrowBook(Member*, Book*)
        +bool returnBook(Member*, Book*)
        +void displayMemberLoans(const Member*) const
        +void displayAllLoans() const
    }

    class Book {
        -string title
        -string author
        -string isbn
        -bool isAvailable
        +Book(string, string, string)
        +string getTitle() const
        +string getAuthor() const
        +string getISBN() const
        +bool getAvailability() const
        +void setAvailability(bool)
    }

    class Member {
        -string memberId
        -string name
        -string contact
        -vector~Book*~ borrowedBooks
        +Member(string, string, string)
        +string getMemberId() const
        +string getName() const
        +string getContact() const
        +const vector~Book*~& getBorrowedBooks() const
        +void borrowBook(Book*)
        +void returnBook(Book*)
        +bool isBorrowing(const Book*) const
    }

    class Loan {
        -Member* member
        -Book* book
        -string borrowDate
        -string returnDate
        +Loan(Member*, Book*, string)
        +Member* getMember() const
        +Book* getBook() const
        +string getBorrowDate() const
        +string getReturnDate() const
        +void setReturnDate(string)
    }

    class CsvDataManager {
        +static bool saveBooksToCsv(const LibraryCatalog&, const string&)
        +static bool loadBooksFromCsv(LibraryCatalog&, const string&)
        +static bool saveMembersToCsv(const MemberManager&, const string&)
        +static bool loadMembersFromCsv(MemberManager&, const string&, LibraryCatalog&)
        -static string formatBookToCsvLine(const Book&)
        -static string formatMemberToCsvLine(const Member&)
        -static Book* parseBookFromCsvLine(const string&)
        -static Member* parseMemberFromCsvLine(const string&, LibraryCatalog&)
    }

    LibrarySystem "1" *-- "1" LibraryCatalog : manages
    LibrarySystem "1" *-- "1" MemberManager : manages
    LibrarySystem "1" *-- "1" LoanManager : manages

    LibraryCatalog "1" o-- "*" Book : contains
    MemberManager "1" o-- "*" Member : contains
    LoanManager "1" o-- "*" Loan : manages

    Loan "1" -- "1" Member : relates to
    Loan "1" -- "1" Book : relates to

    Member "1" --> "*" Book : borrows (via borrowedBooks)

    CsvDataManager ..> LibraryCatalog : uses
    CsvDataManager ..> MemberManager : uses
    CsvDataManager ..> Book : uses
    CsvDataManager ..> Member : uses

