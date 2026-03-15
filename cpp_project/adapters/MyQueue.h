#pragma once
#include "../sequence/MyLinkedList.h"
#include <stdexcept>

template <typename T>
class MyQueue {
public:
    MyQueue();
    MyQueue(const MyQueue& other);
    MyQueue& operator=(const MyQueue& other);
    MyQueue(MyQueue&& other) noexcept;
    MyQueue& operator=(MyQueue&& other) noexcept;

    void enqueue(const T& value);
    void dequeue();
    T& front();
    const T& front() const;
    T& back();
    bool empty() const;
    size_t size() const;
    void clear();

private:
    MyLinkedList<T> container_;
};

#include "MyQueue.cpp"
