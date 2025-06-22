#include "MemberManager.h"

// ������ ����
MemberManager::MemberManager() {
    std::cout << "MemberManager created." << std::endl;
}

// �Ҹ��� ����
MemberManager::~MemberManager() {
    std::cout << "MemberManager destroying..." << std::endl;
    // ���� ��ȸ�ϸ� �������� �Ҵ�� Member ��ü���� delete
    for (auto it = membersById.begin(); it != membersById.end(); ++it) {
        string memberId = it->first;
        Member* member_ptr = it->second;
        std::cout << "Deleting member: " << member_ptr->getName() << " (" << memberId << ")" << std::endl;
        delete member_ptr; // Member ��ü�� �޸� ����
    }
    membersById.clear(); // �� ����
    std::cout << "MemberManager destroyed." << std::endl;
}

// ȸ�� ��� �޼��� ����
bool MemberManager::registerMember(const std::string& memberId, const std::string& name, const std::string& contact) {
    // �̹� ���� ID�� ȸ���� �ִ��� Ȯ��
    if (membersById.count(memberId)) {
        std::cerr << "Error: Member with ID " << memberId << " already exists." << std::endl;
        return false; // �̹� �����ϸ� ��� ����
    }

    // ���ο� Member ��ü�� �������� ����
    Member* newMember = new Member(memberId, name, contact);

    // �ʿ� �߰�
    membersById[memberId] = newMember;
    std::cout << "Member registered: " << name << " (" << memberId << ")" << std::endl;
    return true; // ��� ����
}

// ȸ�� ID�� ȸ�� �˻� �޼��� ����
Member* MemberManager::findMemberById(const std::string& memberId) const {
    // �ʿ��� ID�� �˻�
    auto it = membersById.find(memberId);
    if (it != membersById.end()) {
        // ã������ �ش� Member* ������ ��ȯ
        return it->second;
    }
    // �� ã������ nullptr ��ȯ
    return nullptr;
}

// ȸ�� Ż�� �޼��� ����
bool MemberManager::removeMember(const std::string& memberId) {
    // �ʿ��� ID�� ȸ�� ã��
    auto it = membersById.find(memberId);
    if (it == membersById.end()) {
        std::cerr << "Error: Member with ID " << memberId << " not found for removal." << std::endl;
        return false; // ȸ���� ������ Ż�� ����
    }

    // ã�� Member ��ü�� �޸� ����
    delete it->second;

    // �ʿ��� �ش� �׸� ����
    membersById.erase(it);
    std::cout << "Member removed: " << memberId << std::endl;
    return true; // Ż�� ����
}

// ��� ȸ�� ���� ��� �޼��� ����
void MemberManager::displayAllMembers() const {
    if (membersById.empty()) {
        std::cout << "There are no members registered." << std::endl;
        return;
    }

    std::cout << "\n--- Member List ---" << std::endl;
    // ���� Ű(Member ID) ������ ���ĵǾ� ��ȸ
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

// ��� ȸ�� ID ��� ��ȯ �޼��� ����
std::vector<std::string> MemberManager::getAllMemberIds() const {
    std::vector<std::string> memberIds;
    memberIds.reserve(membersById.size()); // �̸� ũ�⸦ �����Ͽ� ȿ���� ���

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