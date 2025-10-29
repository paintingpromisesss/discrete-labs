#include <vector>
#include <string>
#include <iostream>

unsigned long long dp(int n, const std::string &s)
{
    std::vector<std::vector<unsigned long long>> table(n, std::vector<unsigned long long>(n, 0));

    for (int i = 0; i < n; ++i)
    {
        table[i][i] = 1;
    }

    for (int length = 2; length <= n; ++length)
    {
        for (int i = 0; i <= n - length; ++i)
        {
            int j = i + length - 1;

            if (s[i] != s[j])
            {
                table[i][j] = table[i + 1][j] + table[i][j - 1] - table[i + 1][j - 1];
            }
            else
            {
                table[i][j] = table[i + 1][j] + table[i][j - 1] + 1;
            }
        }
    }
    return table[0][n - 1];
}

int main()
{
    std::string s;
    std::cin >> s;
    int n = s.length();
    std::cout << dp(n, s) << std::endl;
    return 0;
}