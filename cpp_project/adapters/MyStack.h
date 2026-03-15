#pragma once
#include "../sequence/MyVector.h"
#include <stdexcept>

template <typename T>
class MyStack {
public:
    MyStack();
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);
    MyStack(MyStack&& other) noexcept;
    MyStack& operator=(MyStack&& other) noexcept;

    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    size_t size() const;
    void clear();

private:
    MyVector<T> container_;
};

#include "MyStack.cpp"
