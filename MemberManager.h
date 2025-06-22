#ifndef MEMBER_MANAGER_H
#define MEMBER_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Member.h" // Member 클래스 정의 필요

// 회원 목록을 관리하는 클래스 (GRASP: 정보 전문가, 생성자)
class MemberManager {
public:
    // 생성자
    MemberManager();

    // 소멸자
    ~MemberManager();

    // 복사 생성자 및 대입 연산자 방지
    MemberManager(const MemberManager&) = delete;
    MemberManager& operator=(const MemberManager&) = delete;

    // 회원 등록
    bool registerMember(const std::string& memberId, const std::string& name, const std::string& contact);

    // 회원 ID로 회원 검색
    Member* findMemberById(const std::string& memberId) const;

    // 회원 탈퇴
    bool removeMember(const std::string& memberId);

    // 모든 회원 정보 출력
    void displayAllMembers() const;

    // 모든 회원 ID 목록 반환
    std::vector<std::string> getAllMemberIds() const;
    void addMemberPointer(Member* member);

private:
    std::map<std::string, Member*> membersById; // 회원 ID를 키로 Member* 저장
};

#endif // MEMBER_MANAGER_H