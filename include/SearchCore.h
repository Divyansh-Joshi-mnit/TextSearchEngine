#ifndef SEARCH_CORE_H
#define SEARCH_CORE_H
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class SearchCore {
public:
    SearchCore();
    void loadFiles(const std::string& fileListPath);
    void buildIndex();
    void search(const std::string& query);
    void multiSearch(const std::string& queryLine);

private:
    std::vector<std::string> docList;  // List of .txt files
    std::unordered_map<std::string, std::unordered_map<int, int>> wordIndex; // word -> {docID -> frequency}
    
    std::string sanitizeToken(const std::string& token);
    void indexDocument(const std::string& filePath, int docID);
    std::string getFileName(int docID);
};

#endif
