#include "MyUnorderedMap.h"

template <typename K, typename V>
MyUnorderedMap<K, V>::MyUnorderedMap(size_t buckets)
    : buckets_(buckets), size_(0), bucketCount_(buckets) {}

template <typename K, typename V>
MyUnorderedMap<K, V>::MyUnorderedMap(const MyUnorderedMap& other)
    : buckets_(other.buckets_), size_(other.size_), bucketCount_(other.bucketCount_) {}

template <typename K, typename V>
MyUnorderedMap<K, V>& MyUnorderedMap<K, V>::operator=(const MyUnorderedMap& other) {
    if (this != &other) { buckets_ = other.buckets_; size_ = other.size_; bucketCount_ = other.bucketCount_; }
    return *this;
}

template <typename K, typename V>
MyUnorderedMap<K, V>::MyUnorderedMap(MyUnorderedMap&& other) noexcept
    : buckets_(std::move(other.buckets_)), size_(other.size_), bucketCount_(other.bucketCount_) {
    other.size_        = 0;
    other.bucketCount_ = 0;
}

template <typename K, typename V>
MyUnorderedMap<K, V>& MyUnorderedMap<K, V>::operator=(MyUnorderedMap&& other) noexcept {
    if (this != &other) {
        buckets_           = std::move(other.buckets_);
        size_              = other.size_;
        bucketCount_       = other.bucketCount_;
        other.size_        = 0;
        other.bucketCount_ = 0;
    }
    return *this;
}

template <typename K, typename V>
size_t MyUnorderedMap<K, V>::bucketIndex(const K& key) const {
    return std::hash<K>{}(key) % bucketCount_;
}

template <typename K, typename V>
void MyUnorderedMap<K, V>::rehash(size_t newCount) {
    std::vector<std::list<Pair>> nb(newCount);
    for (auto& b : buckets_)
        for (auto& p : b)
            nb[std::hash<K>{}(p.first) % newCount].push_back(p);
    buckets_     = std::move(nb);
    bucketCount_ = newCount;
}

template <typename K, typename V>
V& MyUnorderedMap<K, V>::operator[](const K& key) {
    if (size_ >= bucketCount_ * 2) rehash(bucketCount_ * 2);
    size_t idx = bucketIndex(key);
    for (auto& p : buckets_[idx]) if (p.first == key) return p.second;
    buckets_[idx].push_back({key, V{}});
    ++size_;
    return buckets_[idx].back().second;
}

template <typename K, typename V>
bool MyUnorderedMap<K, V>::insert(const K& key, const V& value) {
    if (size_ >= bucketCount_ * 2) rehash(bucketCount_ * 2);
    size_t idx = bucketIndex(key);
    for (auto& p : buckets_[idx]) if (p.first == key) return false;
    buckets_[idx].push_back({key, value});
    ++size_;
    return true;
}

template <typename K, typename V>
bool MyUnorderedMap<K, V>::erase(const K& key) {
    size_t idx = bucketIndex(key);
    auto& b = buckets_[idx];
    for (auto it = b.begin(); it != b.end(); ++it) {
        if (it->first == key) { b.erase(it); --size_; return true; }
    }
    return false;
}

template <typename K, typename V>
bool MyUnorderedMap<K, V>::contains(const K& key) const {
    for (const auto& p : buckets_[bucketIndex(key)]) if (p.first == key) return true;
    return false;
}

template <typename K, typename V>
V& MyUnorderedMap<K, V>::at(const K& key) {
    for (auto& p : buckets_[bucketIndex(key)]) if (p.first == key) return p.second;
    throw std::out_of_range("MyUnorderedMap::at - key not found");
}

template <typename K, typename V>
const V& MyUnorderedMap<K, V>::at(const K& key) const {
    for (const auto& p : buckets_[bucketIndex(key)]) if (p.first == key) return p.second;
    throw std::out_of_range("MyUnorderedMap::at - key not found");
}

template <typename K, typename V>
size_t MyUnorderedMap<K, V>::size()  const { return size_; }
template <typename K, typename V>
bool   MyUnorderedMap<K, V>::empty() const { return size_ == 0; }

template <typename K, typename V>
void MyUnorderedMap<K, V>::clear() { for (auto& b : buckets_) b.clear(); size_ = 0; }
