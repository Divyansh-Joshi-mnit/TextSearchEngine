#include<iostream>
#include "../include/SearchCore.h"
#include<sstream>
using namespace std;

int main(int argc, char* argv[]) {
   

    // --- Handle Command-Line Arguments ---
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--help") {
            std::cout << "Usage: TextSearchEngine [options]\n\n";
            std::cout << "Options:\n";
            std::cout << "  --help                 Show this help message\n";
            std::cout << "  word1 word2 ...        Search words directly from CLI\n";
            std::cout << "  (no arguments)         Start interactive search mode\n";
            return 0;
        } 
    }

    SearchCore engine;
    string listFile = "data/fileList.txt";
    engine.loadFiles(listFile);
    engine.buildIndex();
    if(argc>1){
        std::ostringstream combined;
        for(int i=1; i<argc; ++i){
            combined << argv[i] << " ";
            if(i!= argc-1) combined << " ";
        }
        std::string combinedSearch  = combined.str();
        std::cout<<"\n [->] Searching for: " << combinedSearch << "\n";
        engine.multiSearch(combinedSearch);
        return 0;
    }

    string input;
    while(true){
        cout<<"\n[->] Enter a word to search (or type 'q' to quit): ";
        getline(cin,input);
        if(input == "q" || input == "Q") break;
        engine.search(input);
    }
    cout<<"Goodbye!\n";
    return 0;
}