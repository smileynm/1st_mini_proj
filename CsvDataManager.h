#ifndef CSV_DATA_MANAGER_H
#define CSV_DATA_MANAGER_H

#include <string>
#include <vector>
#include "LibraryCatalog.h" // LibraryCatalog �� Book Ŭ���� ���� ����
#include "MemberManager.h"  // MemberManager �� Member Ŭ���� ���� ����

// ���� ����(Pure Fabrication) ������ ������ ������ ���� Ŭ����
class CsvDataManager {
public:
    // å �����͸� CSV ���Ϸ� ����
    static bool saveBooksToCsv(const LibraryCatalog& catalog, const std::string& filePath);

    // CSV ���Ͽ��� å �����͸� �ҷ��� īŻ�α׿� �߰�
    static bool loadBooksFromCsv(LibraryCatalog& catalog, const std::string& filePath);

    // ȸ�� �����͸� CSV ���Ϸ� ����
    static bool saveMembersToCsv(const MemberManager& memberManager, const std::string& filePath);

    // CSV ���Ͽ��� ȸ�� �����͸� �ҷ��� ȸ�� �����ڿ� �߰�
    static bool loadMembersFromCsv(MemberManager& memberManager, const std::string& filePath, LibraryCatalog& catalog);

private:
    // CSV �Ľ� �� ������ ���� ���� �Լ� �� (�ʿ�� �߰�)
    // ��: static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::string formatBookToCsvLine(const Book& book);
    static std::string formatMemberToCsvLine(const Member& member);
    static Book* parseBookFromCsvLine(const std::string& line);
    static Member* parseMemberFromCsvLine(const std::string& line, LibraryCatalog& catalog);
};

#endif // CSV_DATA_MANAGER_H
