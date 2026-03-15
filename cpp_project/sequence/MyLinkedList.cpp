#include "MyLinkedList.h"
#include <iostream>

template <typename T>
MyLinkedList<T>::MyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
MyLinkedList<T>::MyLinkedList(const MyLinkedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
    Node* cur = other.head_;
    while (cur) { push_back(cur->data); cur = cur->next; }
}

template <typename T>
MyLinkedList<T>& MyLinkedList<T>::operator=(const MyLinkedList& other) {
    if (this != &other) {
        clear();
        Node* cur = other.head_;
        while (cur) { push_back(cur->data); cur = cur->next; }
    }
    return *this;
}

template <typename T>
MyLinkedList<T>::MyLinkedList(MyLinkedList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
MyLinkedList<T>& MyLinkedList<T>::operator=(MyLinkedList&& other) noexcept {
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
MyLinkedList<T>::~MyLinkedList() { clear(); }

template <typename T>
void MyLinkedList<T>::push_front(const T& value) {
    Node* node = new Node(value);
    node->next = head_;
    head_ = node;
    if (!tail_) tail_ = head_;
    ++size_;
}

template <typename T>
void MyLinkedList<T>::push_back(const T& value) {
    Node* node = new Node(value);
    if (!tail_) { head_ = tail_ = node; }
    else { tail_->next = node; tail_ = node; }
    ++size_;
}

template <typename T>
void MyLinkedList<T>::pop_front() {
    if (!head_) throw std::underflow_error("pop_front on empty list");
    Node* temp = head_;
    head_ = head_->next;
    if (!head_) tail_ = nullptr;
    delete temp;
    --size_;
}

template <typename T>
void MyLinkedList<T>::pop_back() {
    if (!head_) throw std::underflow_error("pop_back on empty list");
    if (head_ == tail_) { delete head_; head_ = tail_ = nullptr; --size_; return; }
    Node* cur = head_;
    while (cur->next != tail_) cur = cur->next;
    delete tail_;
    tail_ = cur;
    tail_->next = nullptr;
    --size_;
}

template <typename T>
T& MyLinkedList<T>::front() {
    if (!head_) throw std::underflow_error("front on empty list");
    return head_->data;
}

template <typename T>
T& MyLinkedList<T>::back() {
    if (!tail_) throw std::underflow_error("back on empty list");
    return tail_->data;
}

template <typename T>
bool   MyLinkedList<T>::empty() const { return size_ == 0; }
template <typename T>
size_t MyLinkedList<T>::size()  const { return size_; }

template <typename T>
void MyLinkedList<T>::clear() {
    while (head_) { Node* t = head_; head_ = head_->next; delete t; }
    tail_ = nullptr; size_ = 0;
}

template <typename T>
bool MyLinkedList<T>::contains(const T& value) const {
    for (Node* c = head_; c; c = c->next) if (c->data == value) return true;
    return false;
}

template <typename T>
void MyLinkedList<T>::remove(const T& value) {
    while (head_ && head_->data == value) pop_front();
    if (!head_) return;
    Node* cur = head_;
    while (cur->next) {
        if (cur->next->data == value) {
            Node* t = cur->next;
            cur->next = t->next;
            if (t == tail_) tail_ = cur;
            delete t; --size_;
        } else { cur = cur->next; }
    }
}

template <typename T>
void MyLinkedList<T>::print() const {
    std::cout << "[";
    for (Node* c = head_; c; c = c->next) {
        std::cout << c->data;
        if (c->next) std::cout << " -> ";
    }
    std::cout << "]\n";
}
