#include "MyStack.h"
#include <utility>

template <typename T>
MyStack<T>::MyStack() {}

template <typename T>
MyStack<T>::MyStack(const MyStack& other) : container_(other.container_) {}

template <typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    if (this != &other) container_ = other.container_;
    return *this;
}

template <typename T>
MyStack<T>::MyStack(MyStack&& other) noexcept : container_(std::move(other.container_)) {}

template <typename T>
MyStack<T>& MyStack<T>::operator=(MyStack&& other) noexcept {
    if (this != &other) container_ = std::move(other.container_);
    return *this;
}

template <typename T>
void MyStack<T>::push(const T& value) { container_.push_back(value); }

template <typename T>
void MyStack<T>::pop() {
    if (empty()) throw std::underflow_error("pop on empty stack");
    container_.pop_back();
}

template <typename T>
T& MyStack<T>::top() {
    if (empty()) throw std::underflow_error("top on empty stack");
    return container_.back();
}

template <typename T>
const T& MyStack<T>::top() const {
    if (empty()) throw std::underflow_error("top on empty stack");
    return container_.back();
}

template <typename T>
bool   MyStack<T>::empty() const { return container_.empty(); }
template <typename T>
size_t MyStack<T>::size()  const { return container_.size(); }
template <typename T>
void   MyStack<T>::clear()       { container_.clear(); }
