    #include "MyVector.h"

template <typename T>
MyVector<T>::MyVector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : data_(nullptr), size_(0), capacity_(0) {
    reserve(other.capacity_);
    for (size_t i = 0; i < other.size_; ++i) data_[i] = other.data_[i];
    size_ = other.size_;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] data_;
        data_ = nullptr; size_ = 0; capacity_ = 0;
        reserve(other.capacity_);
        for (size_t i = 0; i < other.size_; ++i) data_[i] = other.data_[i];
        size_ = other.size_;
    }
    return *this;
}

template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_     = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_           = other.data_;
        size_           = other.size_;
        capacity_       = other.capacity_;
        other.data_     = nullptr;
        other.size_     = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() { delete[] data_; }

template <typename T>
void MyVector<T>::grow() {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
}

template <typename T>
void MyVector<T>::reserve(size_t newCapacity) {
    if (newCapacity <= capacity_) return;
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size_; ++i) newData[i] = data_[i];
    delete[] data_;
    data_     = newData;
    capacity_ = newCapacity;
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (size_ == capacity_) grow();
    data_[size_++] = value;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (size_ == 0) throw std::underflow_error("pop_back on empty vector");
    --size_;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) { return data_[index]; }

template <typename T>
const T& MyVector<T>::operator[](size_t index) const { return data_[index]; }

template <typename T>
T& MyVector<T>::at(size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
T& MyVector<T>::front() {
    if (size_ == 0) throw std::underflow_error("front on empty vector");
    return data_[0];
}

template <typename T>
T& MyVector<T>::back() {
    if (size_ == 0) throw std::underflow_error("back on empty vector");
    return data_[size_ - 1];
}

template <typename T>
bool   MyVector<T>::empty()    const { return size_ == 0; }
template <typename T>
size_t MyVector<T>::size()     const { return size_; }
template <typename T>
size_t MyVector<T>::capacity() const { return capacity_; }
template <typename T>
void   MyVector<T>::clear()          { size_ = 0; }
