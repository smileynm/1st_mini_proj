#ifndef MEMBER_MANAGER_H
#define MEMBER_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Member.h" // Member Ŭ���� ���� �ʿ�

// ȸ�� ����� �����ϴ� Ŭ���� (GRASP: ���� ������, ������)
class MemberManager {
public:
    // ������
    MemberManager();

    // �Ҹ���
    ~MemberManager();

    // ���� ������ �� ���� ������ ����
    MemberManager(const MemberManager&) = delete;
    MemberManager& operator=(const MemberManager&) = delete;

    // ȸ�� ���
    bool registerMember(const std::string& memberId, const std::string& name, const std::string& contact);

    // ȸ�� ID�� ȸ�� �˻�
    Member* findMemberById(const std::string& memberId) const;

    // ȸ�� Ż��
    bool removeMember(const std::string& memberId);

    // ��� ȸ�� ���� ���
    void displayAllMembers() const;

    // ��� ȸ�� ID ��� ��ȯ
    std::vector<std::string> getAllMemberIds() const;
    void addMemberPointer(Member* member);

private:
    std::map<std::string, Member*> membersById; // ȸ�� ID�� Ű�� Member* ����
};

#endif // MEMBER_MANAGER_H