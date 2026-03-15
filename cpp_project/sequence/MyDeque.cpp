#include "MyDeque.h"

template <typename T>
MyDeque<T>::MyDeque() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) : head_(nullptr), tail_(nullptr), size_(0) {
    for (Node* c = other.head_; c; c = c->next) push_back(c->data);
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) {
    if (this != &other) { clear(); for (Node* c = other.head_; c; c = c->next) push_back(c->data); }
    return *this;
}

template <typename T>
MyDeque<T>::MyDeque(MyDeque&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(MyDeque&& other) noexcept {
    if (this != &other) {
        clear();
        head_       = other.head_;
        tail_       = other.tail_;
        size_       = other.size_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
MyDeque<T>::~MyDeque() { clear(); }

template <typename T>
void MyDeque<T>::push_front(const T& value) {
    Node* node = new Node(value);
    node->next = head_;
    if (head_) head_->prev = node;
    head_ = node;
    if (!tail_) tail_ = head_;
    ++size_;
}

template <typename T>
void MyDeque<T>::push_back(const T& value) {
    Node* node = new Node(value);
    node->prev = tail_;
    if (tail_) tail_->next = node;
    tail_ = node;
    if (!head_) head_ = tail_;
    ++size_;
}

template <typename T>
void MyDeque<T>::pop_front() {
    if (!head_) throw std::underflow_error("pop_front on empty deque");
    Node* t = head_;
    head_ = head_->next;
    if (head_) head_->prev = nullptr; else tail_ = nullptr;
    delete t; --size_;
}

template <typename T>
void MyDeque<T>::pop_back() {
    if (!tail_) throw std::underflow_error("pop_back on empty deque");
    Node* t = tail_;
    tail_ = tail_->prev;
    if (tail_) tail_->next = nullptr; else head_ = nullptr;
    delete t; --size_;
}

template <typename T>
T& MyDeque<T>::front() { if (!head_) throw std::underflow_error("front on empty deque"); return head_->data; }
template <typename T>
const T& MyDeque<T>::front() const { if (!head_) throw std::underflow_error("front on empty deque"); return head_->data; }
template <typename T>
T& MyDeque<T>::back() { if (!tail_) throw std::underflow_error("back on empty deque"); return tail_->data; }
template <typename T>
const T& MyDeque<T>::back() const { if (!tail_) throw std::underflow_error("back on empty deque"); return tail_->data; }

template <typename T>
T& MyDeque<T>::operator[](size_t index) {
    Node* c = head_;
    for (size_t i = 0; i < index; ++i) c = c->next;
    return c->data;
}

template <typename T>
const T& MyDeque<T>::operator[](size_t index) const {
    Node* c = head_;
    for (size_t i = 0; i < index; ++i) c = c->next;
    return c->data;
}

template <typename T>
T& MyDeque<T>::at(size_t index) {
    if (index >= size_) throw std::out_of_range("Deque index out of range");
    return operator[](index);
}

template <typename T>
bool   MyDeque<T>::empty() const { return size_ == 0; }
template <typename T>
size_t MyDeque<T>::size()  const { return size_; }

template <typename T>
void MyDeque<T>::clear() {
    while (head_) { Node* t = head_; head_ = head_->next; delete t; }
    tail_ = nullptr; size_ = 0;
}
