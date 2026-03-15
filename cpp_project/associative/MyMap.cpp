#include "MyMap.h"

template <typename K, typename V>
MyMap<K, V>::MyMap() : root_(nullptr), size_(0) {}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap& other) : root_(nullptr), size_(0) {
    root_ = copyNode(other.root_);
    size_ = other.size_;
}

template <typename K, typename V>
MyMap<K, V>& MyMap<K, V>::operator=(const MyMap& other) {
    if (this != &other) { clear(); root_ = copyNode(other.root_); size_ = other.size_; }
    return *this;
}

template <typename K, typename V>
MyMap<K, V>::MyMap(MyMap&& other) noexcept : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
}

template <typename K, typename V>
MyMap<K, V>& MyMap<K, V>::operator=(MyMap&& other) noexcept {
    if (this != &other) {
        clear();
        root_       = other.root_;
        size_       = other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename K, typename V>
MyMap<K, V>::~MyMap() { clear(); }

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::copyNode(Node* node) {
    if (!node) return nullptr;
    Node* n  = new Node(node->key, node->value);
    n->left  = copyNode(node->left);
    n->right = copyNode(node->right);
    return n;
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::insertNode(Node* node, const K& key, const V& value, bool& inserted) {
    if (!node) { inserted = true; return new Node(key, value); }
    if      (key < node->key) node->left  = insertNode(node->left,  key, value, inserted);
    else if (key > node->key) node->right = insertNode(node->right, key, value, inserted);
    return node;
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::findMin(Node* node) const {
    while (node->left) node = node->left;
    return node;
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::eraseNode(Node* node, const K& key, bool& erased) {
    if (!node) return nullptr;
    if      (key < node->key) node->left  = eraseNode(node->left,  key, erased);
    else if (key > node->key) node->right = eraseNode(node->right, key, erased);
    else {
        erased = true;
        if (!node->left)  { Node* t = node->right; delete node; return t; }
        if (!node->right) { Node* t = node->left;  delete node; return t; }
        Node* s = findMin(node->right);
        node->key   = s->key;
        node->value = s->value;
        bool dummy  = false;
        node->right = eraseNode(node->right, s->key, dummy);
    }
    return node;
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::findNode(Node* node, const K& key) const {
    if (!node)          return nullptr;
    if (key == node->key) return node;
    if (key < node->key)  return findNode(node->left,  key);
    return                       findNode(node->right, key);
}

template <typename K, typename V>
void MyMap<K, V>::clearNode(Node* node) {
    if (!node) return;
    clearNode(node->left); clearNode(node->right); delete node;
}

template <typename K, typename V>
void MyMap<K, V>::inorder(Node* node, std::vector<Pair>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back({node->key, node->value});
    inorder(node->right, result);
}

template <typename K, typename V>
V& MyMap<K, V>::operator[](const K& key) {
    Node* f = findNode(root_, key);
    if (f) return f->value;
    bool ins = false;
    root_ = insertNode(root_, key, V{}, ins);
    if (ins) ++size_;
    return findNode(root_, key)->value;
}

template <typename K, typename V>
bool MyMap<K, V>::insert(const K& key, const V& value) {
    bool ins = false;
    root_ = insertNode(root_, key, value, ins);
    if (ins) ++size_;
    return ins;
}

template <typename K, typename V>
bool MyMap<K, V>::erase(const K& key) {
    bool er = false;
    root_ = eraseNode(root_, key, er);
    if (er) --size_;
    return er;
}

template <typename K, typename V>
bool MyMap<K, V>::contains(const K& key) const { return findNode(root_, key) != nullptr; }

template <typename K, typename V>
V& MyMap<K, V>::at(const K& key) {
    Node* f = findNode(root_, key);
    if (!f) throw std::out_of_range("MyMap::at - key not found");
    return f->value;
}

template <typename K, typename V>
const V& MyMap<K, V>::at(const K& key) const {
    Node* f = findNode(root_, key);
    if (!f) throw std::out_of_range("MyMap::at - key not found");
    return f->value;
}

template <typename K, typename V>
size_t MyMap<K, V>::size()  const { return size_; }
template <typename K, typename V>
bool   MyMap<K, V>::empty() const { return size_ == 0; }

template <typename K, typename V>
void MyMap<K, V>::clear() { clearNode(root_); root_ = nullptr; size_ = 0; }

template <typename K, typename V>
std::vector<typename MyMap<K, V>::Pair> MyMap<K, V>::toSortedVector() const {
    std::vector<Pair> res;
    inorder(root_, res);
    return res;
}
