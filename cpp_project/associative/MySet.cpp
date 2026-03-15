#include "MySet.h"

template <typename T>
MySet<T>::MySet() : root_(nullptr), size_(0) {}

template <typename T>
MySet<T>::MySet(const MySet& other) : root_(nullptr), size_(0) {
    root_ = copyNode(other.root_);
    size_ = other.size_;
}

template <typename T>
MySet<T>& MySet<T>::operator=(const MySet& other) {
    if (this != &other) { clear(); root_ = copyNode(other.root_); size_ = other.size_; }
    return *this;
}

template <typename T>
MySet<T>::MySet(MySet&& other) noexcept : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
}

template <typename T>
MySet<T>& MySet<T>::operator=(MySet&& other) noexcept {
    if (this != &other) {
        clear();
        root_       = other.root_;
        size_       = other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
MySet<T>::~MySet() { clear(); }

template <typename T>
typename MySet<T>::Node* MySet<T>::copyNode(Node* node) {
    if (!node) return nullptr;
    Node* n  = new Node(node->data);
    n->left  = copyNode(node->left);
    n->right = copyNode(node->right);
    return n;
}

template <typename T>
typename MySet<T>::Node* MySet<T>::insertNode(Node* node, const T& value, bool& inserted) {
    if (!node) { inserted = true; return new Node(value); }
    if      (value < node->data) node->left  = insertNode(node->left,  value, inserted);
    else if (value > node->data) node->right = insertNode(node->right, value, inserted);
    return node;
}

template <typename T>
typename MySet<T>::Node* MySet<T>::findMin(Node* node) const {
    while (node->left) node = node->left;
    return node;
}

template <typename T>
typename MySet<T>::Node* MySet<T>::eraseNode(Node* node, const T& value, bool& erased) {
    if (!node) return nullptr;
    if      (value < node->data) node->left  = eraseNode(node->left,  value, erased);
    else if (value > node->data) node->right = eraseNode(node->right, value, erased);
    else {
        erased = true;
        if (!node->left)  { Node* t = node->right; delete node; return t; }
        if (!node->right) { Node* t = node->left;  delete node; return t; }
        Node* s = findMin(node->right);
        node->data = s->data;
        bool dummy = false;
        node->right = eraseNode(node->right, s->data, dummy);
    }
    return node;
}

template <typename T>
bool MySet<T>::containsNode(Node* node, const T& value) const {
    if (!node)             return false;
    if (value == node->data) return true;
    if (value < node->data)  return containsNode(node->left,  value);
    return                         containsNode(node->right, value);
}

template <typename T>
void MySet<T>::clearNode(Node* node) {
    if (!node) return;
    clearNode(node->left); clearNode(node->right); delete node;
}

template <typename T>
void MySet<T>::inorder(Node* node, std::vector<T>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->data);
    inorder(node->right, result);
}

template <typename T>
bool MySet<T>::insert(const T& value) {
    bool ins = false;
    root_ = insertNode(root_, value, ins);
    if (ins) ++size_;
    return ins;
}

template <typename T>
bool MySet<T>::erase(const T& value) {
    bool er = false;
    root_ = eraseNode(root_, value, er);
    if (er) --size_;
    return er;
}

template <typename T>
bool   MySet<T>::contains(const T& value) const { return containsNode(root_, value); }
template <typename T>
size_t MySet<T>::size()  const { return size_; }
template <typename T>
bool   MySet<T>::empty() const { return size_ == 0; }

template <typename T>
void MySet<T>::clear() { clearNode(root_); root_ = nullptr; size_ = 0; }

template <typename T>
std::vector<T> MySet<T>::toSortedVector() const {
    std::vector<T> res;
    inorder(root_, res);
    return res;
}
