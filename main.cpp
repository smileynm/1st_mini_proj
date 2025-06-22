#define _CRT_SECURE_NO_WARNINGS
#include "LibrarySystem.h" // LibrarySystem Ŭ���� ���� ����
#include "CsvDataManager.h" // ������ �ε�/������ ���� �ʿ�

int main() {
    // ������ ���� ��� ����
    const std::string bookFilePath = "books.csv";
    const std::string memberFilePath = "members.csv";

    // LibrarySystem ��ü ����
    LibrarySystem librarySystem;

    // ���α׷� ���� �� CSV ���Ͽ��� ������ �ε�
    cout << "Loading data from CSV files..." << endl;
    CsvDataManager::loadBooksFromCsv(librarySystem.getCatalog(), bookFilePath);
    CsvDataManager::loadMembersFromCsv(librarySystem.getMemberManager(),
        memberFilePath, librarySystem.getCatalog());
    std::cout << "Data loading complete." << std::endl;

    // LibrarySystem�� ���� ���� ���� ����
    librarySystem.run();

    // ���α׷� ���� �� ���� �����͸� CSV ���Ͽ� ����
    std::cout << "Saving data to CSV files..." << std::endl;
    CsvDataManager::saveBooksToCsv(librarySystem.getCatalog(), bookFilePath); // LibrarySystem�� getCatalog() �޼��� �ʿ� ����
    CsvDataManager::saveMembersToCsv(librarySystem.getMemberManager(), memberFilePath); // LibrarySystem�� getMemberManager() �޼��� �ʿ� ����
    std::cout << "Data saving complete." << std::endl;


    return 0; // ���α׷� ���� ����
}