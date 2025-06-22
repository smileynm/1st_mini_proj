#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include "LibraryCatalog.h"
#include "MemberManager.h"
#include "LoanManager.h"

// �ý����� ��ü �帧�� �����ϴ� ��Ʈ�ѷ� Ŭ���� (GRASP: Controller)
class LibrarySystem {
public:
    // ������
    LibrarySystem();

    // �Ҹ���
    ~LibrarySystem();

    // �ý��� ���� ���� ����
    void run();

    // ������ ��ü�� ���� ������ (Getter) - CsvDataManager���� ���
    LibraryCatalog& getCatalog();
    MemberManager& getMemberManager();
    LoanManager& getLoanManager(); // �ʿ��ϴٸ� LoanManager�� �߰�

private:
    LibraryCatalog catalog;
    MemberManager memberManager;
    LoanManager loanManager;

    // ����� �������̽� �� ��� ó�� ���� �޼���
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
    // ���� ��� �߰�
    void handleExit();
};

#endif // LIBRARY_SYSTEM_H