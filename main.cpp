#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

class Treap
{
    struct Node
    {
        std::string key;
        uint64_t value;
        int priority;
        Node *left;
        Node *right;
        Node(std::string key, uint64_t value) : key(key), value(value), priority(rand()), left(nullptr), right(nullptr) {}
    };

    Node *root;

public:
    Node *getRoot() const { return root; }

    Node *find(Node *node, std::string key)
    {
        if (!node)
        {
            return nullptr;
        }

        if (key < node->key)
        {
            return find(node->left, key);
        }
        else if (key > node->key)
        {
            return find(node->right, key);
        }
        else
        {
            return node;
        }
    }

    Node *insert(Node *node, std::string key, uint64_t value)
    {
        if (!node)
            return new Node(key, value);

        if (key < node->key)
        {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key, value);
        }
        return node;
    }

    Node *findMax(Node *node)
    {
        while (node && node->right)
        {
            node = node->right;
        }

        return node;
    }

    Node *remove(Node *node, std::string key)
    {
        if (!node)
            return nullptr;
        if (key < node->key)
        {
            node->left = remove(node->left, key);
            return node;
        }
        else if (key > node->key)
        {
            node->right = remove(node->right, key);
            return node;
        }

        if (node->left && node->right)
        {
            Node *prev = findMax(node->left);
            node->key = prev->key;
            node->value = prev->value;
            node->left = remove(node->left, node->key);
            return node;
        }

        Node *temp = node;
        if (node->left)
        {
            node = node->left;
        }
        else if (node->right)
        {
            node = node->right;
        }
        else
        {
            node = nullptr;
        }
        delete temp;
        return node;
    }

    std::pair<Node *, Node *> split(Node *node, std::string key)
    {
        if (!node)
            return std::pair<Node *, Node *>(nullptr, nullptr);

        if (key <= node->key)
        {
            auto splitted = split(node->left, key);

            auto left = splitted.first;
            auto right = splitted.second;

            node->left = right;

            return std::pair<Node *, Node *>(left, node);
        }

        auto splitted = split(node->right, key);
        auto left = splitted.first;
        auto right = splitted.second;

        node->right = left;

        return std::pair<Node *, Node *>(node, right);
    }

    Node *merge(Node *leftNode, Node *rightNode)
    {
        if (!leftNode)
            return rightNode;
        if (!rightNode)
            return leftNode;

        if (leftNode->priority >= rightNode->priority)
        {
            leftNode->right = merge(leftNode->right, rightNode);
            return leftNode;
        }

        rightNode->left = merge(leftNode, rightNode->left);

        return rightNode;
    }

public:
    Treap() : root(nullptr) {}

    bool insert(std::string key, uint64_t value)
    {
        toLower(key);
        auto [exists, _] = search(key);
        if (exists)
            return false;
        auto splitted = split(root, key);
        auto left = splitted.first;
        auto right = splitted.second;

        left = merge(left, new Node(key, value));
        root = merge(left, right);
        return true;
    }

    std::pair<bool, uint64_t> search(std::string key)
    {
        toLower(key);
        auto node = find(root, key);
        if (!node)
        {
            return {false, 0};
        }
        return {true, node->value};
    }

    void toLower(std::string &key)
    {
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    }

    bool remove(std::string key)
    {
        toLower(key);
        auto [exists, _] = search(key);
        if (!exists)
            return false;

        auto splitted = split(root, key);
        auto left = splitted.first;
        auto right = splitted.second;

        right = remove(right, key);
        root = merge(left, right);
        return true;
    }

    void print(Node *node)
    {
        if (!node)
            return;
        print(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        print(node->right);
    }
};

int main()
{
    Treap dictionary;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line == "exit")
            break;
        if (line == "print")
        {
            dictionary.print(dictionary.getRoot());
            continue;
        }

        if (line[0] == '+')
        {
            size_t space_pos = line.find(' ', 2);
            if (space_pos == std::string::npos)
                continue;

            std::string word = line.substr(2, space_pos - 2);
            uint64_t number = std::stoull(line.substr(space_pos + 1));

            if (dictionary.insert(word, number))
            {
                std::cout << "OK" << std::endl;
            }
            else
            {
                std::cout << "Exist" << std::endl;
            }
        }
        else if (line[0] == '-')
        {
            std::string word = line.substr(2);
            if (dictionary.remove(word))
            {
                std::cout << "OK" << std::endl;
            }
            else
            {
                std::cout << "NoSuchWord" << std::endl;
            }
        }
        else
        {
            std::string word = line;
            word.erase(0, word.find_first_not_of(" \t\n\r"));
            word.erase(word.find_last_not_of(" \t\n\r") + 1);

            auto [found, value] = dictionary.search(word);
            if (found)
            {
                std::cout << "OK: " << value << std::endl;
            }
            else
            {
                std::cout << "NoSuchWord" << std::endl;
            }
        }
    }
    return 0;
}