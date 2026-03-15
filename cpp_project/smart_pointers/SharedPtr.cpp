#include "SharedPtr.h"
#include <stdexcept>

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : ptr_(ptr), ref_count_(nullptr) {
    if (ptr_) ref_count_ = new long(1);
}

template <typename T>
SharedPtr<T>::~SharedPtr() { release(); }

template <typename T>
void SharedPtr<T>::release() {
    if (ref_count_) {
        if (--(*ref_count_) == 0) { delete ptr_; delete ref_count_; }
        ptr_ = nullptr; ref_count_ = nullptr;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    if (ref_count_) ++(*ref_count_);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
    if (this != &other) {
        release();
        ptr_ = other.ptr_; ref_count_ = other.ref_count_;
        if (ref_count_) ++(*ref_count_);
    }
    return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr; other.ref_count_ = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        release();
        ptr_ = other.ptr_; ref_count_ = other.ref_count_;
        other.ptr_ = nullptr; other.ref_count_ = nullptr;
    }
    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*() const {
    if (!ptr_) throw std::runtime_error("Dereferencing null SharedPtr");
    return *ptr_;
}

template <typename T>
T*   SharedPtr<T>::operator->()  const { return ptr_; }
template <typename T>
T*   SharedPtr<T>::get()         const { return ptr_; }
template <typename T>
long SharedPtr<T>::use_count()   const { return ref_count_ ? *ref_count_ : 0; }

template <typename T>
void SharedPtr<T>::reset(T* ptr) { release(); ptr_ = ptr; if (ptr_) ref_count_ = new long(1); }

template <typename T>
SharedPtr<T>::operator bool() const { return ptr_ != nullptr; }
