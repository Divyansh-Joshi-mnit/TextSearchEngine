#include "../include/SearchCore.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<cctype>
#include<filesystem>


namespace fs = std::filesystem;

SearchCore::SearchCore(){}

void SearchCore::loadFiles(const std::string& fileListPath){
    std::ifstream infile(fileListPath);
    std::string path;
    while(std::getline(infile,path)){
        if(!path.empty()){
            docList.push_back(path);
        }
    }
}

void SearchCore::buildIndex(){
    for(int i=0;i<docList.size();++i){
        std::cout<<"[Indexing]"<< docList[i]<<std::endl;
        indexDocument(docList[i],i);
    }
    std::cout<<"[Done] Indexing complete.\n";
}


void SearchCore::indexDocument(const std::string& filePath, int docID){
    std::ifstream file(filePath);
    std:: string line;
    while(std::getline(file,line)){
        std:: stringstream ss(line);
        std:: string word;
        while(ss>>word){
            std:: string cleaned = sanitizeToken(word);

            if(!cleaned.empty()){
                std:: transform(cleaned.begin(),cleaned.end(),cleaned.begin(),::tolower);
                wordIndex[cleaned][docID]++;
            }
        }
    }
}

std::string SearchCore:: sanitizeToken(const std::string& token){
    std::string result;
    for(char c: token){
        if(std:: isalpha(static_cast<unsigned char>(c))){
            result+=c;
        }
    }
    return result;
}

void SearchCore::search(const std:: string& query){
    std:: string cleaned = sanitizeToken(query);
    std:transform(cleaned.begin(),cleaned.end(),cleaned.begin(),::tolower);
    if(cleaned.empty()){
        std::cout<<"[!] Invalid input.\n";
        return;
    }
    std::cout << "[Searching] '" << query << "'\n";
    std::ofstream logFile("output/output.txt", std::ios::app);
    logFile << "[Search] " << query << "\n";

    auto it = wordIndex.find(cleaned);
    if (it == wordIndex.end()) {
        std::cout << "[ FAIL ] No results found for '" << query << "'\n";
        logFile << "  |=> Not found in any file\n\n";
        return;
    }

    std::cout << "[ OK ] Results for '" << query << "':\n";
    for (const auto& [docID, count] : it->second) {
        std::string fileName = getFileName(docID);
        std::cout << "  |=> " << fileName << " (" << count << " occurrences)\n";
        logFile << "  |=> " << fileName << " (" << count << " occurrences)\n";
    }
    logFile << "\n";
}

std:: string SearchCore::getFileName(int docID){
    if(docID>=0 && docID < docList.size()){
        return docList[docID];
    }
    return "[Unknown File] !";
}