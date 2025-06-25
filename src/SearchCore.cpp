#include "../include/SearchCore.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #error "Missing the <filesystem> or <experimental/filesystem> header."
#endif


SearchCore::SearchCore() {}

void SearchCore::loadFiles(const std::string& fileListPath) {
    std::ifstream infile(fileListPath);
    std::string path;
    while (std::getline(infile, path)) {
        if (!path.empty()) {
            docList.push_back(path);
        }
    }
}

void SearchCore::buildIndex() {
    for (int i = 0; i < docList.size(); ++i) {
        std::cout << "\033[34m[Indexing]\033[0m " << docList[i] << std::endl;
        indexDocument(docList[i], i);
    }
    std::cout << "\033[36m[Done]\033[0m Indexing complete.\n";
}

void SearchCore::indexDocument(const std::string& filePath, int docID) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            std::string cleaned = sanitizeToken(word);
            if (!cleaned.empty()) {
                std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
                wordIndex[cleaned][docID]++;
            }
        }
    }
}

std::string SearchCore::sanitizeToken(const std::string& token) {
    std::string result;
    for (size_t i = 0; i < token.size(); ++i) {
        char c = token[i];

        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += c;
        }
        else if (c == '-' || c == '_' || c == '+' || c == '.') {
            // Allow hyphen/underscore/plus/period if surrounded by alphanum
            if (i > 0 && i < token.size() - 1 &&
                std::isalnum(static_cast<unsigned char>(token[i - 1])) &&
                std::isalnum(static_cast<unsigned char>(token[i + 1]))) {
                result += c;
            }
        }
    }
    return result;
}

void SearchCore::search(const std::string& query) {
    std::string cleaned = sanitizeToken(query);
    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);

    if (cleaned.empty()) {
        std::cout << "\033[33m[!] Invalid input.\033[0m\n";
        return;
    }

    std::cout << "\033[36m[Searching]\033[0m '" << query << "'\n";
    std::ofstream logFile("output/output.txt", std::ios::app);
    logFile << "[Search] " << query << "\n";

    auto it = wordIndex.find(cleaned);
    if (it == wordIndex.end()) {
        std::cout << "\033[31m[ FAIL ]\033[0m No results found for '" << query << "'\n";
        logFile << "  |=> Not found in any file\n\n";
        return;
    }

    std::cout << "\033[32m[ OK ]\033[0m Results for '" << query << "':\n";
    for (const auto& [docID, count] : it->second) {
        std::string fileName = getFileName(docID);
        std::cout << "  |=> " << fileName << " (" << count << " occurrences)\n";
        logFile << "  |=> " << fileName << " (" << count << " occurrences)\n";
    }
    logFile << "\n";
}

void SearchCore::multiSearch(const std::string& queryLine) {
    std::istringstream ss(queryLine);
    std::string token;
    std::set<int> matchingDocs;
    std::ofstream logFile("output/output.txt", std::ios::app);
    std::vector<std::string> searchWords;

    while (ss >> token) {
        std::string cleaned = sanitizeToken(token);
        std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
        if (!cleaned.empty()) {
            searchWords.push_back(cleaned);
        }
    }

    if (searchWords.empty()) {
        std::cout << "\033[33m[!] No valid search terms provided.\033[0m\n";
        logFile << "[Search] (invalid empty input)\n\n";
        return;
    }

    logFile << "[Search] ";
    for (const std::string& w : searchWords) logFile << w << " ";
    logFile << "\n";

    std::set<int> resultSet;
    bool firstWord = true;

    for (const std::string& word : searchWords) {
        auto it = wordIndex.find(word);
        std::set<int> wordDocs;
        if (it != wordIndex.end()) {
            for (const auto& [docID, freq] : it->second) {
                wordDocs.insert(docID);
            }
        }

        if (firstWord) {
            resultSet = wordDocs;
            firstWord = false;
        } else {
            std::set<int> temp;
            std::set_intersection(resultSet.begin(), resultSet.end(),
                                  wordDocs.begin(), wordDocs.end(),
                                  std::inserter(temp, temp.begin()));
            resultSet = temp;
        }
    }

    if (resultSet.empty()) {
        std::cout << "\033[31m[✘] No files matched all search terms.\033[0m\n";
        logFile << "  ↪ Not found in any file\n\n";
    } else {
        std::cout << "\033[32m[✔] Found in:\033[0m\n";
        for (int docID : resultSet) {
            int totalCount = 0;
            for (const std::string& word : searchWords) {
                totalCount += wordIndex[word][docID];
            }

            std::string fileName = getFileName(docID);
            std::cout << "  ↪ " << fileName << " (" << totalCount << " total occurrences)\n";
            logFile << "  ↪ " << fileName << " (" << totalCount << " total occurrences)\n";
        }
        logFile << "\n";
    }
}

std::string SearchCore::getFileName(int docID) {
    if (docID >= 0 && docID < docList.size()) {
        return docList[docID];
    }
    return "[Unknown File] !";
}
