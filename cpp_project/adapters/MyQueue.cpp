#include "MyQueue.h"
#include <utility>

template <typename T>
MyQueue<T>::MyQueue() {}

template <typename T>
MyQueue<T>::MyQueue(const MyQueue& other) : container_(other.container_) {}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other) {
    if (this != &other) container_ = other.container_;
    return *this;
}

template <typename T>
MyQueue<T>::MyQueue(MyQueue&& other) noexcept : container_(std::move(other.container_)) {}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue&& other) noexcept {
    if (this != &other) container_ = std::move(other.container_);
    return *this;
}

template <typename T>
void MyQueue<T>::enqueue(const T& value) { container_.push_back(value); }

template <typename T>
void MyQueue<T>::dequeue() {
    if (empty()) throw std::underflow_error("dequeue on empty queue");
    container_.pop_front();
}

template <typename T>
T& MyQueue<T>::front() {
    if (empty()) throw std::underflow_error("front on empty queue");
    return container_.front();
}

template <typename T>
const T& MyQueue<T>::front() const {
    if (empty()) throw std::underflow_error("front on empty queue");
    return container_.front();
}

template <typename T>
T& MyQueue<T>::back() {
    if (empty()) throw std::underflow_error("back on empty queue");
    return container_.back();
}

template <typename T>
bool   MyQueue<T>::empty() const { return container_.empty(); }
template <typename T>
size_t MyQueue<T>::size()  const { return container_.size(); }
template <typename T>
void   MyQueue<T>::clear()       { container_.clear(); }
