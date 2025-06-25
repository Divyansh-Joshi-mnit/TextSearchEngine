#include <iostream>
#include <sstream>
#include "../include/SearchCore.h"

int main(int argc, char* argv[]) {
    // --- Handle Command-Line Arguments First ---
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--help") {
            std::cout << "\033[36mUsage: TextSearchEngine [options]\033[0m\n\n";
            std::cout << "Options:\n";
            std::cout << "  \033[33m--help\033[0m                 Show this help message\n";
            std::cout << "  \033[33mword1 word2 ...\033[0m        Search words directly from CLI\n";
            std::cout << "  \033[33m(no arguments)\033[0m         Start interactive search mode\n";
            return 0;
        }
    }

    // --- Initialize search engine ---
    SearchCore engine;
    std::string listFile = "data/fileList.txt";
    engine.loadFiles(listFile);
    engine.buildIndex();

    // --- CLI argument-based search ---
    if (argc > 1) {
        std::ostringstream combined;
        for (int i = 1; i < argc; ++i) {
            combined << argv[i];
            if (i != argc - 1) combined << " ";
        }
        std::string combinedSearch = combined.str();
        std::cout << "\n\033[36m[->] Searching for:\033[0m " << combinedSearch << "\n";
        engine.multiSearch(combinedSearch);
        return 0;
    }

    // --- Interactive search mode ---
    std::string input;
    while (true) {
        std::cout << "\n\033[36m[->] Enter word(s) to search (or type 'q' to quit):\033[0m ";
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") break;
        engine.multiSearch(input);
    }
    std::cout << "\033[36m[Exit]\033[0m Goodbye!\n";
    return 0;
}
