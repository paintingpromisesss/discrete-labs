#pragma once
#include <string>
#include <cstdint>
#include <algorithm>

class Treap {
    struct Node {
        std::string key;
        uint64_t value;
        int priority;
        Node *left;
        Node *right;
        Node(std::string &k, uint64_t v) : key(k), value(v), priority(rand()), left(nullptr), right(nullptr) {}
    };

    Node *root;

    Node *find(Node *node, const std::string &key) {
        if (!node) return nullptr;

        if (node->key == key){
            return node;
        }

        if (key < node->key) {
            return find(node->left, key);
        }

        return find(node->right, key);
    }


    Node *insert(Node *node, std::string &key, uint64_t value) {
        if (!node) return new Node(key, value);

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        return node;
    }

    Node *findMax(Node *node) {
        while (node && node->right) {
            node = node->right;
        }

        return node;
    }

    Node *remove(Node *node, std::string &key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
        } else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        }

        if (!node->left && !node->right) {
            auto prev = findMax(node->left);

            node->key = prev->key;

            node->left = remove(node->left, node->key);

            return node;
        }

        auto temp = node;
        if (node->left) {
            node = node->left;
        } else if (node->right) {
            node = node->right;
        } else {
            node = nullptr;
        }
        
        delete temp;

        return node;
    }


    std::pair<Node*, Node*> split(Node *node, std::string &key) {
        if (!node) return std::pair<Node*, Node*>(nullptr, nullptr);

        if (key < node->key) {
            auto splitted = split(node->right, key);

            auto left= splitted.first;
            auto right= splitted.second;

            node->right = left;

            return std::pair<Node*, Node*>(node, right);
        }
    }

    Node *merge(Node *leftNode, Node *rightNode) {
        if (!leftNode) return rightNode;
        if (!rightNode) return leftNode;

        if (leftNode->priority > rightNode->priority) {
            leftNode->right = merge(leftNode->right, rightNode);
            return leftNode;
        }

        rightNode->left = merge(leftNode, rightNode->left);

        return rightNode;

    }


public:
    Treap() : root(nullptr) {}

    bool insert(std::string &key, uint64_t value) {
        if (search(key) == -1) return false;

        auto splitted = split(root, key);
        auto left = splitted.first;
        auto right = splitted.second;

        left = merge(left, new Node(key, value));
        root = merge(left, right);
        return true;
    }

    int64_t search(std::string key) {
        toLower(key);
        auto node = find(root, key);
        if (!node) return -1;
        return node->value;
    }

    void toLower(std::string &key) {
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    }

    bool remove(std::string &key) {
        if(!search(key)) return false;

        auto splitted = split(root, key);
        auto left = splitted.first;
        auto right = splitted.second;

        right = remove(right, key);
        merge(left, right);
        return true;
    }

};
