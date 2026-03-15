#pragma once
#include <stdexcept>
#include <cstddef>

template <typename T>
class MyVector {
public:
    MyVector();
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    void push_back(const T& value);
    void pop_back();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    T& front();
    T& back();
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void clear();
    void reserve(size_t newCapacity);

private:
    T* data_;
    size_t size_;
    size_t capacity_;
    void grow();
};

#include "MyVector.cpp"
