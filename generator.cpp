#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>

std::mt19937_64 rng(std::random_device{}());

void generate_data(const std::string& filename, int min_key, int max_key, size_t num_pairs) {
    std::ofstream out(filename);
    std::uniform_int_distribution<unsigned short> key_dist(min_key, max_key);
    std::uniform_int_distribution<unsigned long long> value_dist(0, UINT64_MAX);

    for (size_t i = 0; i < num_pairs; ++i) {
        out << key_dist(rng) << "\t" << value_dist(rng) << "\n";
    }
}

int main() {
    // 1. Узкий диапазон (10 ключей, 1M пар)
    generate_data("./data/narrow_range.txt", 1000, 1009, 10'000'000);

    // 2. Широкий диапазон (все 65536 ключей, 1M пар)
    generate_data("./data/wide_range.txt", 0, 65535, 10'000'000);

    // 3. Один ключ (1M пар)
    generate_data("./data/single_key.txt", 42, 42, 10'000'000);

    std::cout << "Данные сгенерированы.\n";
    return 0;
}