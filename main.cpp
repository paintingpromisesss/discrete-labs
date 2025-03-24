#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>

const int MAX = 65536;

void countSort(std::vector<std::pair<unsigned short, unsigned long long>> &data) {
    std::vector<unsigned int> counts(MAX, 0);

    for (size_t i = 0; i < data.size(); i++) {
        counts[data[i].first]++;
    }

    for (size_t i = 1; i < MAX; i++) {
        counts[i] += counts[i - 1];
    }

    std::vector <std::pair<unsigned short, unsigned long long>> sortedData(data.size());
    for (int i = data.size() - 1; i >= 0; i--) {
        sortedData[counts[data[i].first] - 1] = data[i];
        counts[data[i].first]--;
    }
    std::ofstream outFile("output.txt");
    for (size_t i = 0; i < sortedData.size(); i++) {
        outFile << sortedData[i].first << "\t" << sortedData[i].second << std::endl;
    }
    outFile.close();
}


int main() {
    std::vector<std::pair<unsigned short, unsigned long long>> data;
    std::ifstream inFile("input.txt");
    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        unsigned short first;
        unsigned long long second;
        if (iss >> first >> second) {
            data.push_back(std::make_pair(first, second));
        }
    }
    inFile.close();

    countSort(data);
    return 0;
}