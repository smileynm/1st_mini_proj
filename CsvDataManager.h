#ifndef CSV_DATA_MANAGER_H
#define CSV_DATA_MANAGER_H

#include <string>
#include <vector>
#include "LibraryCatalog.h" // LibraryCatalog 및 Book 클래스 선언 포함
#include "MemberManager.h"  // MemberManager 및 Member 클래스 선언 포함

// 순수 조작(Pure Fabrication) 패턴을 적용한 데이터 관리 클래스
class CsvDataManager {
public:
    // 책 데이터를 CSV 파일로 저장
    static bool saveBooksToCsv(const LibraryCatalog& catalog, const std::string& filePath);

    // CSV 파일에서 책 데이터를 불러와 카탈로그에 추가
    static bool loadBooksFromCsv(LibraryCatalog& catalog, const std::string& filePath);

    // 회원 데이터를 CSV 파일로 저장
    static bool saveMembersToCsv(const MemberManager& memberManager, const std::string& filePath);

    // CSV 파일에서 회원 데이터를 불러와 회원 관리자에 추가
    static bool loadMembersFromCsv(MemberManager& memberManager, const std::string& filePath, LibraryCatalog& catalog);

private:
    // CSV 파싱 및 포맷팅 관련 헬퍼 함수 등 (필요시 추가)
    // 예: static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::string formatBookToCsvLine(const Book& book);
    static std::string formatMemberToCsvLine(const Member& member);
    static Book* parseBookFromCsvLine(const std::string& line);
    static Member* parseMemberFromCsvLine(const std::string& line, LibraryCatalog& catalog);
};

#endif // CSV_DATA_MANAGER_H
