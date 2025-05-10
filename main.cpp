#include <vector>
#include <string>
#include <iostream>

std::vector<int> z_function(const std::string& s) {
    int n = s.size();
    std::vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text, pattern;
    std::cin >> text >> pattern;

    std::string concat = pattern + '$' + text;
    std::vector<int> z = z_function(concat);
    int pat_len = pattern.size();

    for (int i = pat_len + 1; i < (int)z.size(); ++i) {
        if (z[i] == pat_len) {
            std::cout << (i - pat_len - 1) << "\n";
        }
    }
    return 0;
}