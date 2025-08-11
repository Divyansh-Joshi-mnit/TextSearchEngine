#include <iostream>
#include <sstream>
#include "../include/SearchCore.h"
#include <fstream>
#define APP_VERSION "1.0.0"
#define APP_NAME "TextSearchEngine"
int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--help") {
            std::cout << "\033[36mUsage: TextSearchEngine [options]\033[0m\n\n";
            std::cout << "Options:\n";
            std::cout << "  \033[33m--help\033[0m           Show this help message\n";
            std::cout << "  \033[33mword1 word2 ...\033[0m  Search words directly from CLI\n";
            std::cout << "  \033[33m(no arguments)\033[0m     Start interactive search mode\n\n";

            std::cout << "Interactive Commands:\n";
            std::cout << "  \033[33m/history\033[0m         Show previous searches\n";
            std::cout << "  \033[33m/clear\033[0m           Clear log file\n";
            std::cout << "  \033[33m/reset\033[0m           Rebuild index from fileList\n";
            std::cout << "  \033[33m/version\033[0m         Show version info\n";
            std::cout << "  \033[33m/quit\033[0m            Exit the program\n";

            return 0;
        }
    }

    SearchCore engine;
    std::string listFile = "data/fileList.txt";
    engine.loadFiles(listFile);
    engine.buildIndex();
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
    std::string input;
    while (true) {
        std::cout << "\n\033[36m[->] Enter word(s) to search (or type 'q' to quit):\033[0m ";
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") break;
        if (input == "/history") {
            std::ifstream log("output/output.txt");
        if (!log.is_open()) {
            std::cout << "\033[31m[✘] No history found.\033[0m\n";
        }   else {
            std::cout << "\033[36m[History Log:]\033[0m\n";
            std::string line;
            while (std::getline(log, line)) {
                std::cout << line << "\n";
                }
            }
            continue;
        }

        if (input == "/version") {
        std::cout << "\033[36m[TextSearchEngine v" << APP_VERSION << "]\033[0m Built with C++17\n";
        continue;
       }
       if (input == "/clear") {
            std::ofstream clearFile("output/output.txt", std::ios::trunc);
            std::cout << "\033[33m[!] Log file cleared.\033[0m\n";
            continue;
        }
        if (input == "/reset") {
        std::ofstream clearFile("output/output.txt", std::ios::trunc);
        std::cout << "\033[33m[!] Log file cleared. Rebuilding index...\033[0m\n";
        engine = SearchCore(); 
        engine.loadFiles("data/fileList.txt");
        engine.buildIndex();
        continue;
         } 
        if (input.empty()) {
            std::cout << "\033[33m[!] Empty input. Please enter a search term.\033[0m\n";
            continue;
        }

    if (input == "/quit") break;

        engine.multiSearch(input);
    }
    std::cout << "\033[36m[Exit]\033[0m Goodbye!\n";
    return 0;
}
