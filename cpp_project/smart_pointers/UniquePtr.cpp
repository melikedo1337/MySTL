#include "UniquePtr.h"
#include <stdexcept>

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr) : ptr_(ptr) {}

template <typename T>
UniquePtr<T>::~UniquePtr() { delete ptr_; }

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
    if (this != &other) { delete ptr_; ptr_ = other.ptr_; other.ptr_ = nullptr; }
    return *this;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
    if (!ptr_) throw std::runtime_error("Dereferencing null UniquePtr");
    return *ptr_;
}

template <typename T>
T* UniquePtr<T>::operator->() const { return ptr_; }

template <typename T>
T* UniquePtr<T>::get() const { return ptr_; }

template <typename T>
T* UniquePtr<T>::release() { T* t = ptr_; ptr_ = nullptr; return t; }

template <typename T>
void UniquePtr<T>::reset(T* ptr) { delete ptr_; ptr_ = ptr; }

template <typename T>
UniquePtr<T>::operator bool() const { return ptr_ != nullptr; }
