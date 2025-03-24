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

    data = std::move(sortedData);
}


int main() {
    std::vector<std::pair<unsigned short, unsigned long long>> data;
    std::ifstream inFile("input.txt");
    unsigned short first;
    unsigned long long second;
    while (inFile >> first >> second) {
        data.push_back(std::make_pair(first, second));
    }


    countSort(data);
    std::ofstream outFile("output.txt");
    for (size_t i = 0; i < data.size(); i++) {
        outFile << data[i].first << "\t" << data[i].second << std::endl;
    }
    outFile.close();
    return 0;
}