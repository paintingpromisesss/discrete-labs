#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> build_suffix_array(const std::string &text)
{
    int n = text.size();
    std::vector<int> suffix_array(n);

    for (int i = 0; i < n; i++)
    {
        suffix_array[i] = i;
    }
    std::sort(suffix_array.begin(), suffix_array.end(), [&text](int a, int b)
              { return std::lexicographical_compare(text.begin() + a, text.end(), text.begin() + b, text.end()); });

    return suffix_array;
}

std::vector<int> find_indices(const std::vector<int> &suffix_array, const std::string &text, const std::string &pattern)
{
    std::vector<int> indices;
    if (pattern.empty())
        return indices;

    int left = 0, right = suffix_array.size();
    while (left < right)
    {
        int mid = (left + right) / 2;
        int cmp = text.compare(suffix_array[mid], pattern.size(), pattern);
        if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    int lower = left;

    right = suffix_array.size();
    while (left < right)
    {
        int mid = (left + right) / 2;
        int cmp = text.compare(suffix_array[mid], pattern.size(), pattern);
        if (cmp <= 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    int upper = left;

    for (int i = lower; i < upper; i++)
    {
        indices.push_back(suffix_array[i] + 1);
    }

    std::sort(indices.begin(), indices.end());
    return indices;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::getline(std::cin, text);
    std::vector<int> suffix_array = build_suffix_array(text);

    std::string pattern;
    int counter = 1;

    while (std::getline(std::cin, pattern))
    {
        if (pattern.empty())
            continue;

        std::vector<int> indices = find_indices(suffix_array, text, pattern);
        if (!indices.empty())
        {
            std::cout << counter << ": ";
            for (size_t i = 0; i < indices.size(); i++)
            {
                if (i > 0)
                    std::cout << ", ";
                std::cout << indices[i];
            }
            std::cout << "\n";
        }
        counter++;
    }
    return 0;
}
