#ifndef LOAN_MANAGER_H
#define LOAN_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include "Loan.h"

class Member; // Forward declaration
class Book;   // Forward declaration
//class Loan;   // Forward declaration

// ���� ������ ����ϴ� Ŭ���� (GRASP: ���� ������, ������)
class LoanManager {
public:
    // ���� ó��
    bool borrowBook(Member* member, Book* book);

    // �ݳ� ó��
    bool returnBook(Member* member, Book* book);

    // Ư�� ȸ���� ���� ��� ���
    void displayMemberLoans(const Member* member) const;

    // ��ü ���� ��� ���
    void displayAllLoans() const;

private:
    std::vector<Loan> currentLoans; // ���� ���� ���
};

#endif // LOAN_MANAGER_H
