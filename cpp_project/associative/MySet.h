#pragma once
#include <stdexcept>
#include <cstddef>
#include <vector>

template <typename T>
class MySet {
public:
    MySet();
    MySet(const MySet& other);
    MySet& operator=(const MySet& other);
    MySet(MySet&& other) noexcept;
    MySet& operator=(MySet&& other) noexcept;
    ~MySet();

    bool insert(const T& value);
    bool erase(const T& value);
    bool contains(const T& value) const;
    size_t size() const;
    bool empty() const;
    void clear();
    std::vector<T> toSortedVector() const;

private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root_;
    size_t size_;

    Node* insertNode(Node* node, const T& value, bool& inserted);
    Node* eraseNode(Node* node, const T& value, bool& erased);
    Node* findMin(Node* node) const;
    bool containsNode(Node* node, const T& value) const;
    void clearNode(Node* node);
    Node* copyNode(Node* node);
    void inorder(Node* node, std::vector<T>& result) const;
};

#include "MySet.cpp"
