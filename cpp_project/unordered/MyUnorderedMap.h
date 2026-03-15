#pragma once
#include <vector>
#include <list>
#include <functional>
#include <utility>
#include <stdexcept>
#include <cstddef>

template <typename K, typename V>
class MyUnorderedMap {
public:
    using Pair = std::pair<K, V>;

    explicit MyUnorderedMap(size_t buckets = 16);
    MyUnorderedMap(const MyUnorderedMap& other);
    MyUnorderedMap& operator=(const MyUnorderedMap& other);
    MyUnorderedMap(MyUnorderedMap&& other) noexcept;
    MyUnorderedMap& operator=(MyUnorderedMap&& other) noexcept;
    ~MyUnorderedMap() = default;

    V& operator[](const K& key);
    bool insert(const K& key, const V& value);
    bool erase(const K& key);
    bool contains(const K& key) const;
    V& at(const K& key);
    const V& at(const K& key) const;
    size_t size() const;
    bool empty() const;
    void clear();

private:
    std::vector<std::list<Pair>> buckets_;
    size_t size_;
    size_t bucketCount_;

    size_t bucketIndex(const K& key) const;
    void rehash(size_t newBucketCount);
};

#include "MyUnorderedMap.cpp"
