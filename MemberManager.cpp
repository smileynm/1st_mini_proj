#include "MemberManager.h"

// 생성자 구현
MemberManager::MemberManager() {
    std::cout << "MemberManager created." << std::endl;
}

// 소멸자 구현
MemberManager::~MemberManager() {
    std::cout << "MemberManager destroying..." << std::endl;
    // 맵을 순회하며 동적으로 할당된 Member 객체들을 delete
    for (auto it = membersById.begin(); it != membersById.end(); ++it) {
        string memberId = it->first;
        Member* member_ptr = it->second;
        std::cout << "Deleting member: " << member_ptr->getName() << " (" << memberId << ")" << std::endl;
        delete member_ptr; // Member 객체의 메모리 해제
    }
    membersById.clear(); // 맵 비우기
    std::cout << "MemberManager destroyed." << std::endl;
}

// 회원 등록 메서드 구현
bool MemberManager::registerMember(const std::string& memberId, const std::string& name, const std::string& contact) {
    // 이미 같은 ID의 회원이 있는지 확인
    if (membersById.count(memberId)) {
        std::cerr << "Error: Member with ID " << memberId << " already exists." << std::endl;
        return false; // 이미 존재하면 등록 실패
    }

    // 새로운 Member 객체를 동적으로 생성
    Member* newMember = new Member(memberId, name, contact);

    // 맵에 추가
    membersById[memberId] = newMember;
    std::cout << "Member registered: " << name << " (" << memberId << ")" << std::endl;
    return true; // 등록 성공
}

// 회원 ID로 회원 검색 메서드 구현
Member* MemberManager::findMemberById(const std::string& memberId) const {
    // 맵에서 ID로 검색
    auto it = membersById.find(memberId);
    if (it != membersById.end()) {
        // 찾았으면 해당 Member* 포인터 반환
        return it->second;
    }
    // 못 찾았으면 nullptr 반환
    return nullptr;
}

// 회원 탈퇴 메서드 구현
bool MemberManager::removeMember(const std::string& memberId) {
    // 맵에서 ID로 회원 찾기
    auto it = membersById.find(memberId);
    if (it == membersById.end()) {
        std::cerr << "Error: Member with ID " << memberId << " not found for removal." << std::endl;
        return false; // 회원이 없으면 탈퇴 실패
    }

    // 찾은 Member 객체의 메모리 해제
    delete it->second;

    // 맵에서 해당 항목 제거
    membersById.erase(it);
    std::cout << "Member removed: " << memberId << std::endl;
    return true; // 탈퇴 성공
}

// 모든 회원 정보 출력 메서드 구현
void MemberManager::displayAllMembers() const {
    if (membersById.empty()) {
        std::cout << "There are no members registered." << std::endl;
        return;
    }

    std::cout << "\n--- Member List ---" << std::endl;
    // 맵은 키(Member ID) 순서로 정렬되어 순회
    for (auto it = membersById.begin(); it != membersById.end(); ++it) {
        string memberId = it->first;
        Member* member_ptr = it->second;
        std::cout << "  ID: " << memberId
            << ", Name: " << member_ptr->getName()
            << ", Contact: " << member_ptr->getContact()
            << std::endl;
    }
    std::cout << "------------------" << std::endl;
}

// 모든 회원 ID 목록 반환 메서드 구현
std::vector<std::string> MemberManager::getAllMemberIds() const {
    std::vector<std::string> memberIds;
    memberIds.reserve(membersById.size()); // 미리 크기를 예약하여 효율성 향상

    for (auto it = membersById.begin(); it != membersById.end(); ++it) {
        string memberId = it->first;
        memberIds.push_back(memberId);
    }
    return memberIds;
}

void MemberManager::addMemberPointer(Member* member)
{
    membersById[member->getMemberId()] = member;
}
