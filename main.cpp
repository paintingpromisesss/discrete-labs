#include <iostream>
#include <string>
#include "treap.hpp"

int main() {
    Treap dictionary;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        if(line == "exit") break;

        if (line[0] == '+') {
            size_t space_pos = line.find(' ', 2);
            if (space_pos == std::string::npos) continue;

            std::string word = line.substr(2, space_pos - 2);
            uint64_t number = std::stoull(line.substr(space_pos + 1));

            if(dictionary.insert(word, number)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "Exist" << word << std::endl;
            }
        } else if (line[0] == '-') {
            std::string word = line.substr(2);
            if (dictionary.remove(word)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "NoSuchWord" << word << std::endl;
            }
        } else {
            std::string word = line;
            int64_t value = dictionary.search(word);
            if (value != -1) {
                std::cout << "OK: " << value << std::endl;
            } else {
                std::cout << "NoSuchWord" << word << std::endl;
            }
        }
    }
    return 0;
}