#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include "LibraryCatalog.h"
#include "MemberManager.h"
#include "LoanManager.h"

// 시스템의 전체 흐름을 제어하는 컨트롤러 클래스 (GRASP: Controller)
class LibrarySystem {
public:
    // 생성자
    LibrarySystem();

    // 소멸자
    ~LibrarySystem();

    // 시스템 메인 실행 루프
    void run();

    // 관리자 객체에 대한 접근자 (Getter) - CsvDataManager에서 사용
    LibraryCatalog& getCatalog();
    MemberManager& getMemberManager();
    LoanManager& getLoanManager(); // 필요하다면 LoanManager도 추가

private:
    LibraryCatalog catalog;
    MemberManager memberManager;
    LoanManager loanManager;

    // 사용자 인터페이스 및 기능 처리 헬퍼 메서드
    void displayMenu();
    void processUserInput();
    void handleAddBook();
    void handleRegisterMember();
    void handleBorrowBook();
    void handleReturnBook();
    void handleSearchBook();
    void handleDisplayAllBooks();
    void handleDisplayAllMembers();
    void handleDisplayMemberLoans();
    void handleDisplayAllLoans();
    // 종료 기능 추가
    void handleExit();
};

#endif // LIBRARY_SYSTEM_H