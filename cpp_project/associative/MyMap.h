#pragma once
#include <stdexcept>
#include <cstddef>
#include <vector>
#include <utility>

template <typename K, typename V>
class MyMap {
public:
    using Pair = std::pair<K, V>;

    MyMap();
    MyMap(const MyMap& other);
    MyMap& operator=(const MyMap& other);
    MyMap(MyMap&& other) noexcept;
    MyMap& operator=(MyMap&& other) noexcept;
    ~MyMap();

    V& operator[](const K& key);
    bool insert(const K& key, const V& value);
    bool erase(const K& key);
    bool contains(const K& key) const;
    V& at(const K& key);
    const V& at(const K& key) const;
    size_t size() const;
    bool empty() const;
    void clear();
    std::vector<Pair> toSortedVector() const;

private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        Node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root_;
    size_t size_;

    Node* insertNode(Node* node, const K& key, const V& value, bool& inserted);
    Node* eraseNode(Node* node, const K& key, bool& erased);
    Node* findMin(Node* node) const;
    Node* findNode(Node* node, const K& key) const;
    void clearNode(Node* node);
    Node* copyNode(Node* node);
    void inorder(Node* node, std::vector<Pair>& result) const;
};

#include "MyMap.cpp"
