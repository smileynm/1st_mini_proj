#define _CRT_SECURE_NO_WARNINGS
#include "LibrarySystem.h" // LibrarySystem 클래스 정의 포함
#include "CsvDataManager.h" // 데이터 로딩/저장을 위해 필요

int main() {
    // 데이터 파일 경로 정의 (예시)
    const std::string bookFilePath = "books.csv";
    const std::string memberFilePath = "members.csv";

    // LibrarySystem 객체 생성
    LibrarySystem librarySystem;

    // 프로그램 시작 시 CSV 파일에서 데이터 로드
    std::cout << "Loading data from CSV files..." << std::endl;
    CsvDataManager::loadBooksFromCsv(librarySystem.getCatalog(), bookFilePath); // LibrarySystem에 getCatalog() 메서드 필요 가정
    CsvDataManager::loadMembersFromCsv(librarySystem.getMemberManager(), memberFilePath, librarySystem.getCatalog()); // LibrarySystem에 getMemberManager() 메서드 필요 가정
    std::cout << "Data loading complete." << std::endl;


    // LibrarySystem의 메인 실행 루프 시작
    librarySystem.run();

    // 프로그램 종료 시 현재 데이터를 CSV 파일에 저장
    std::cout << "Saving data to CSV files..." << std::endl;
    CsvDataManager::saveBooksToCsv(librarySystem.getCatalog(), bookFilePath); // LibrarySystem에 getCatalog() 메서드 필요 가정
    CsvDataManager::saveMembersToCsv(librarySystem.getMemberManager(), memberFilePath); // LibrarySystem에 getMemberManager() 메서드 필요 가정
    std::cout << "Data saving complete." << std::endl;


    return 0; // 프로그램 정상 종료
}
