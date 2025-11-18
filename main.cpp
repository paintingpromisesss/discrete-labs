#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

bool mapContains(const std::unordered_map<std::string, int> &map, const std::string &key)
{
    return map.find(key) != map.end();
}

bool listContains(const std::vector<std::string> &list, const int &key)
{
    return key >= 0 && key < list.size();
}

std::vector<std::string> compressLZW(const std::string &input)
{
    std::unordered_map<std::string, int> compressMap;
    std::vector<std::string> output;
    for (int i = 0; i < 26; i++)
    {
        char ch = 'a' + i;
        compressMap[std::string(1, ch)] = i;
    }
    compressMap["EOF"] = 26;

    std::string current = "";
    int nextCode = 27;
    for (auto &c : input)
    {
        if (mapContains(compressMap, current + c))
        {
            current += c;
        }
        else
        {
            output.push_back(std::to_string(compressMap[current]));
            compressMap[current + c] = nextCode++;
            current = std::string(1, c);
        }
    }

    if (!current.empty())
    {
        output.push_back(std::to_string(compressMap[current]));
    }
    output.push_back("26");
    return output;
}

std::vector<std::string> decompressLZM(const std::vector<int> &input)
{
    std::vector<std::string> decompressList;
    std::vector<std::string> output;
    for (int i = 0; i < 26; i++)
    {
        char ch = 'a' + i;
        decompressList.push_back(std::string(1, ch));
    }
    decompressList.push_back("EOF");

    std::string previous = "";
    int nextCode = 27;

    for (auto &code : input)
    {
        if (code == 26)
        {
            break;
        }
        if (listContains(decompressList, code))
        {
            std::string current = decompressList[code];
            output.push_back(current);
            if (!previous.empty())
            {
                decompressList.push_back(previous + current[0]);
                nextCode++;
            }
            previous = current;
        }
        else
        {
            std::string current = previous + previous[0];
            output.push_back(current);
            decompressList.push_back(current);
            nextCode++;
            previous = current;
        }
    }

    return output;
}

int main()
{
    std::string type;
    std::cin >> type;
    if (type == "compress")
    {
        std::string input;
        std::cin >> input;
        std::vector<std::string> compressed = compressLZW(input);
        for (const auto &code : compressed)
        {
            if (code != "26")
                std::cout << code << " ";
            else
                std::cout << code;
        }
    }
    else if (type == "decompress")
    {
        std::vector<int> codes;
        int inputCode;
        while (std::cin >> inputCode)
        {
            codes.push_back(inputCode);
            if (inputCode == 26)
                break;
        }
        std::vector<std::string> decompressed = decompressLZM(codes);
        for (const auto &str : decompressed)
        {
            std::cout << str;
        }
    }
    return 0;
}