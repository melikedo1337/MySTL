#pragma once
#include <vector>
#include <list>
#include <functional>
#include <cstddef>

template <typename T>
class MyUnorderedSet {
public:
    explicit MyUnorderedSet(size_t buckets = 16);
    MyUnorderedSet(const MyUnorderedSet& other);
    MyUnorderedSet& operator=(const MyUnorderedSet& other);
    MyUnorderedSet(MyUnorderedSet&& other) noexcept;
    MyUnorderedSet& operator=(MyUnorderedSet&& other) noexcept;
    ~MyUnorderedSet() = default;

    bool insert(const T& value);
    bool erase(const T& value);
    bool contains(const T& value) const;
    size_t size() const;
    bool empty() const;
    void clear();

private:
    std::vector<std::list<T>> buckets_;
    size_t size_;
    size_t bucketCount_;

    size_t bucketIndex(const T& value) const;
    void rehash(size_t newBucketCount);
};

#include "MyUnorderedSet.cpp"
