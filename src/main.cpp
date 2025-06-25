#include<iostream>
#include "../include/SearchCore.h"

using namespace std;

int main(int argc, char* argv[]) {
   

    // --- Handle Command-Line Arguments ---
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--help") {
            std::cout << "Usage: TextSearchEngine [options]\n\n";
            std::cout << "Options:\n";
            std::cout << "  --help            Show this help message\n";
            std::cout << "  (no arguments)    Start interactive search mode\n";
            return 0;
        } else {
            std::cout << "[!] Unknown argument: " << arg << "\n";
            std::cout << "Use --help for usage instructions.\n";
            return 1;
        }
    }

    SearchCore engine;
    string listFile = "data/fileList.txt";
    engine.loadFiles(listFile);
    engine.buildIndex();

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