#pragma once
#include <stdexcept>
#include <cstddef>

template <typename T>
class MyLinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    MyLinkedList();
    MyLinkedList(const MyLinkedList& other);
    MyLinkedList& operator=(const MyLinkedList& other);
    MyLinkedList(MyLinkedList&& other) noexcept;
    MyLinkedList& operator=(MyLinkedList&& other) noexcept;
    ~MyLinkedList();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    T& front();
    T& back();
    bool empty() const;
    size_t size() const;
    void clear();
    bool contains(const T& value) const;
    void remove(const T& value);
    void print() const;

private:
    Node* head_;
    Node* tail_;
    size_t size_;
};

#include "MyLinkedList.cpp"
