#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    
    std::vector<std::pair<unsigned short, unsigned long long>> data;
    FILE *inFile = fopen(argv[1], "r");
    unsigned short first;
    unsigned long long second;
    while (fscanf(inFile, "%hu\t%llu", &first, &second) == 2) {
        data.push_back(std::make_pair(first, second));
    }
    fclose(inFile);
    
    clock_t start = clock();

    std::stable_sort(data.begin(), data.end(),
        [](const auto &a, const auto &b) { return a.first < b.first; });
        
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "Elapsed time: " << elapsed << " seconds" << std::endl;
    
    FILE *outFile = fopen(argv[2], "w");
    for (size_t i = 0; i < data.size(); i++) {
        fprintf(outFile, "%hu\t%llu\n", data[i].first, data[i].second);
    }
    fclose(outFile);

    
    return 0;
}