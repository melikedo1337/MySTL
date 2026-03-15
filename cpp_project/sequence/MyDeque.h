#pragma once
#include <stdexcept>
#include <cstddef>

template <typename T>
class MyDeque {
public:
    MyDeque();
    MyDeque(const MyDeque& other);
    MyDeque& operator=(const MyDeque& other);
    MyDeque(MyDeque&& other) noexcept;
    MyDeque& operator=(MyDeque&& other) noexcept;
    ~MyDeque();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    bool empty() const;
    size_t size() const;
    void clear();

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    size_t size_;
};

#include "MyDeque.cpp"
