#pragma once
#include <utility>

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* ptr = nullptr);
    ~SharedPtr();

    SharedPtr(const SharedPtr& other);
    SharedPtr& operator=(const SharedPtr& other);

    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get() const;
    long use_count() const;
    void reset(T* ptr = nullptr);
    explicit operator bool() const;

private:
    T* ptr_;
    long* ref_count_;

    void release();
};

#include "SharedPtr.cpp"
