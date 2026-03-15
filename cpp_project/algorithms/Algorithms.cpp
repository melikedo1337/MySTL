#include "Algorithms.h"

namespace MyAlgorithms {

    template <typename T>
    void bubbleSort(std::vector<T>& arr) {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; ++i)
            for (size_t j = 0; j < n - i - 1; ++j)
                if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
    }

    template <typename T>
    void selectionSort(std::vector<T>& arr) {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; ++i) {
            size_t m = i;
            for (size_t j = i + 1; j < n; ++j) if (arr[j] < arr[m]) m = j;
            if (m != i) std::swap(arr[i], arr[m]);
        }
    }

    template <typename T>
    void insertionSort(std::vector<T>& arr) {
        size_t n = arr.size();
        for (size_t i = 1; i < n; ++i) {
            T key = arr[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; --j; }
            arr[j + 1] = key;
        }
    }

    template <typename T>
    static void merge(std::vector<T>& arr, int l, int m, int r) {
        std::vector<T> L(arr.begin() + l, arr.begin() + m + 1);
        std::vector<T> R(arr.begin() + m + 1, arr.begin() + r + 1);
        int i = 0, j = 0, k = l;
        while (i < (int)L.size() && j < (int)R.size())
            arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        while (i < (int)L.size()) arr[k++] = L[i++];
        while (j < (int)R.size()) arr[k++] = R[j++];
    }

    template <typename T>
    void mergeSort(std::vector<T>& arr, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    template <typename T>
    static int partition(std::vector<T>& arr, int low, int high) {
        T pivot = arr[high]; int i = low - 1;
        for (int j = low; j < high; ++j) if (arr[j] <= pivot) std::swap(arr[++i], arr[j]);
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template <typename T>
    void quickSort(std::vector<T>& arr, int low, int high) {
        if (low < high) { int pi = partition(arr, low, high); quickSort(arr, low, pi - 1); quickSort(arr, pi + 1, high); }
    }

    template <typename T>
    int linearSearch(const std::vector<T>& arr, const T& target) {
        for (size_t i = 0; i < arr.size(); ++i) if (arr[i] == target) return static_cast<int>(i);
        return -1;
    }

    template <typename T>
    int binarySearch(const std::vector<T>& arr, const T& target) {
        int l = 0, r = static_cast<int>(arr.size()) - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (arr[m] == target) return m;
            if (arr[m] < target)  l = m + 1;
            else                  r = m - 1;
        }
        return -1;
    }

    template <typename T>
    T findMin(const std::vector<T>& arr) {
        if (arr.empty()) throw std::runtime_error("findMin on empty array");
        T m = arr[0]; for (size_t i = 1; i < arr.size(); ++i) if (arr[i] < m) m = arr[i]; return m;
    }

    template <typename T>
    T findMax(const std::vector<T>& arr) {
        if (arr.empty()) throw std::runtime_error("findMax on empty array");
        T m = arr[0]; for (size_t i = 1; i < arr.size(); ++i) if (arr[i] > m) m = arr[i]; return m;
    }

    template <typename T>
    void reverseArray(std::vector<T>& arr) {
        int l = 0, r = static_cast<int>(arr.size()) - 1;
        while (l < r) std::swap(arr[l++], arr[r--]);
    }

    template <typename T>
    bool isSorted(const std::vector<T>& arr) {
        for (size_t i = 1; i < arr.size(); ++i) if (arr[i] < arr[i - 1]) return false;
        return true;
    }

}
