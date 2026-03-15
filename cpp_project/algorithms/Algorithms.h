#pragma once
#include <vector>
#include <stdexcept>

namespace MyAlgorithms {

    template <typename T>
    void bubbleSort(std::vector<T>& arr);

    template <typename T>
    void selectionSort(std::vector<T>& arr);

    template <typename T>
    void insertionSort(std::vector<T>& arr);

    template <typename T>
    void mergeSort(std::vector<T>& arr, int left, int right);

    template <typename T>
    void quickSort(std::vector<T>& arr, int low, int high);

    template <typename T>
    int linearSearch(const std::vector<T>& arr, const T& target);

    template <typename T>
    int binarySearch(const std::vector<T>& arr, const T& target);

    template <typename T>
    T findMin(const std::vector<T>& arr);

    template <typename T>
    T findMax(const std::vector<T>& arr);

    template <typename T>
    void reverseArray(std::vector<T>& arr);

    template <typename T>
    bool isSorted(const std::vector<T>& arr);

}

#include "Algorithms.cpp"
