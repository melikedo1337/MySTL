#include "MyUnorderedSet.h"

template <typename T>
MyUnorderedSet<T>::MyUnorderedSet(size_t buckets)
    : buckets_(buckets), size_(0), bucketCount_(buckets) {}

template <typename T>
MyUnorderedSet<T>::MyUnorderedSet(const MyUnorderedSet& other)
    : buckets_(other.buckets_), size_(other.size_), bucketCount_(other.bucketCount_) {}

template <typename T>
MyUnorderedSet<T>& MyUnorderedSet<T>::operator=(const MyUnorderedSet& other) {
    if (this != &other) { buckets_ = other.buckets_; size_ = other.size_; bucketCount_ = other.bucketCount_; }
    return *this;
}

template <typename T>
MyUnorderedSet<T>::MyUnorderedSet(MyUnorderedSet&& other) noexcept
    : buckets_(std::move(other.buckets_)), size_(other.size_), bucketCount_(other.bucketCount_) {
    other.size_        = 0;
    other.bucketCount_ = 0;
}

template <typename T>
MyUnorderedSet<T>& MyUnorderedSet<T>::operator=(MyUnorderedSet&& other) noexcept {
    if (this != &other) {
        buckets_           = std::move(other.buckets_);
        size_              = other.size_;
        bucketCount_       = other.bucketCount_;
        other.size_        = 0;
        other.bucketCount_ = 0;
    }
    return *this;
}

template <typename T>
size_t MyUnorderedSet<T>::bucketIndex(const T& value) const {
    return std::hash<T>{}(value) % bucketCount_;
}

template <typename T>
void MyUnorderedSet<T>::rehash(size_t newCount) {
    std::vector<std::list<T>> nb(newCount);
    for (auto& b : buckets_)
        for (auto& item : b)
            nb[std::hash<T>{}(item) % newCount].push_back(item);
    buckets_     = std::move(nb);
    bucketCount_ = newCount;
}

template <typename T>
bool MyUnorderedSet<T>::insert(const T& value) {
    if (size_ >= bucketCount_ * 2) rehash(bucketCount_ * 2);
    size_t idx = bucketIndex(value);
    for (const auto& item : buckets_[idx]) if (item == value) return false;
    buckets_[idx].push_back(value);
    ++size_;
    return true;
}

template <typename T>
bool MyUnorderedSet<T>::erase(const T& value) {
    size_t idx = bucketIndex(value);
    auto& b = buckets_[idx];
    for (auto it = b.begin(); it != b.end(); ++it) {
        if (*it == value) { b.erase(it); --size_; return true; }
    }
    return false;
}

template <typename T>
bool MyUnorderedSet<T>::contains(const T& value) const {
    size_t idx = bucketIndex(value);
    for (const auto& item : buckets_[idx]) if (item == value) return true;
    return false;
}

template <typename T>
size_t MyUnorderedSet<T>::size()  const { return size_; }
template <typename T>
bool   MyUnorderedSet<T>::empty() const { return size_ == 0; }

template <typename T>
void MyUnorderedSet<T>::clear() {
    for (auto& b : buckets_) b.clear();
    size_ = 0;
}
