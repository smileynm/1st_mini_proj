#ifndef LOAN_MANAGER_H
#define LOAN_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include "Loan.h"

class Member; // Forward declaration
class Book;   // Forward declaration
//class Loan;   // Forward declaration

// 대출 관리를 담당하는 클래스 (GRASP: 정보 전문가, 생성자)
class LoanManager {
public:
    // 대출 처리
    bool borrowBook(Member* member, Book* book);

    // 반납 처리
    bool returnBook(Member* member, Book* book);

    // 특정 회원의 대출 목록 출력
    void displayMemberLoans(const Member* member) const;

    // 전체 대출 기록 출력
    void displayAllLoans() const;

private:
    std::vector<Loan> currentLoans; // 현재 대출 기록
};

#endif // LOAN_MANAGER_H
