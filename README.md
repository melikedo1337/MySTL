# C++ STL Implementations from Scratch

A hand-written C++ project that re-implements the most important parts of the C++ Standard Template Library (STL) from scratch, organized by the same categories the STL uses. Every class is fully templated, has its own `.h` / `.cpp` files, and supports copy semantics, move semantics, and exception safety. A single `main.cpp` runs a comprehensive test suite that covers every feature.

---

## Project Structure

```
cpp_project/
├── sequence/                   # Sequence containers
│   ├── MyVector.h / .cpp       # Dynamic array (like std::vector)
│   ├── MyLinkedList.h / .cpp   # Singly linked list (like std::list)
│   └── MyDeque.h / .cpp        # Double-ended queue (like std::deque)
│
├── associative/                # Ordered associative containers (BST-backed)
│   ├── MySet.h / .cpp          # Unique-key ordered set (like std::set)
│   └── MyMap.h / .cpp          # Key-value ordered map (like std::map)
│
├── unordered/                  # Unordered associative containers (hash-table-backed)
│   ├── MyUnorderedSet.h / .cpp # Hash set (like std::unordered_set)
│   └── MyUnorderedMap.h / .cpp # Hash map (like std::unordered_map)
│
├── adapters/                   # Container adapters
│   ├── MyStack.h / .cpp        # LIFO stack built on MyVector (like std::stack)
│   └── MyQueue.h / .cpp        # FIFO queue built on MyLinkedList (like std::queue)
│
├── smart_pointers/             # Smart pointers
│   ├── UniquePtr.h / .cpp      # Exclusive ownership (like std::unique_ptr)
│   └── SharedPtr.h / .cpp      # Shared ownership with ref-counting (like std::shared_ptr)
│
├── algorithms/                 # Common algorithms
│   └── Algorithms.h / .cpp     # Sorting, searching, and utility algorithms
│
└── main.cpp                    # Full test suite for all implementations
```

---

## What Is Implemented

### Sequence Containers

| Class | Backing Structure | Key Operations |
|---|---|---|
| `MyVector<T>` | Dynamic heap array | `push_back`, `pop_back`, `operator[]`, `at`, `front`, `back`, `reserve`, `clear` |
| `MyLinkedList<T>` | Singly linked list | `push_front`, `push_back`, `pop_front`, `pop_back`, `contains`, `remove`, `print` |
| `MyDeque<T>` | Doubly linked list | `push_front`, `push_back`, `pop_front`, `pop_back`, `operator[]`, `at`, `front`, `back` |

### Associative Containers (ordered, BST-backed)

| Class | Backing Structure | Key Operations |
|---|---|---|
| `MySet<T>` | Binary Search Tree | `insert`, `erase`, `contains`, `toSortedVector` |
| `MyMap<K, V>` | Binary Search Tree | `insert`, `erase`, `contains`, `at`, `operator[]`, `toSortedVector` |

Elements are always stored in sorted order. `toSortedVector()` returns them via in-order traversal.

### Unordered Associative Containers (hash-table-backed)

| Class | Backing Structure | Key Operations |
|---|---|---|
| `MyUnorderedSet<T>` | Hash table (separate chaining) | `insert`, `erase`, `contains` |
| `MyUnorderedMap<K, V>` | Hash table (separate chaining) | `insert`, `erase`, `contains`, `at`, `operator[]` |

Both use `std::hash` internally and automatically rehash when the load factor exceeds 2.

### Container Adapters

| Class | Underlying Container | Key Operations |
|---|---|---|
| `MyStack<T>` | `MyVector<T>` | `push`, `pop`, `top` |
| `MyQueue<T>` | `MyLinkedList<T>` | `enqueue`, `dequeue`, `front`, `back` |

### Smart Pointers

| Class | Semantics | Key Operations |
|---|---|---|
| `UniquePtr<T>` | Exclusive ownership, move-only | `operator*`, `operator->`, `get`, `release`, `reset` |
| `SharedPtr<T>` | Shared ownership with reference counting | `operator*`, `operator->`, `get`, `use_count`, `reset` |

### Algorithms (`MyAlgorithms` namespace)

| Algorithm | Description |
|---|---|
| `bubbleSort` | O(n²) comparison sort |
| `selectionSort` | O(n²) selection sort |
| `insertionSort` | O(n²) insertion sort |
| `mergeSort` | O(n log n) divide-and-conquer sort |
| `quickSort` | O(n log n) average, pivot-based sort |
| `linearSearch` | O(n) unsorted search, returns index or -1 |
| `binarySearch` | O(log n) sorted search, returns index or -1 |
| `findMin` / `findMax` | O(n) min/max scan |
| `reverseArray` | O(n) in-place reversal |
| `isSorted` | O(n) sorted-order check |

---

## Special Member Functions

Every container implements the full set of special member functions:

| Function | Description |
|---|---|
| Default constructor | Creates an empty container |
| Copy constructor | Deep copies all elements |
| Copy assignment operator | Deep copies, handles self-assignment |
| **Move constructor** | Steals internal data in O(1), leaves source empty |
| **Move assignment operator** | Same as move constructor, releases current data first |
| Destructor | Frees all allocated memory |

All move operations are marked `noexcept`.

---

## How to Build and Run

**Requirements:** A C++17-compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

```bash
# Compile
g++ -std=c++17 -Wall -Wextra -o test_runner main.cpp

# Run all tests
./test_runner
```

No external libraries or build system required — a single compile command is enough.

---

## Example Output

```
=== SEQUENCE CONTAINERS ===
  [PASS] Move constructor: ownership transferred, source emptied
  [PASS] Move assignment: ownership transferred, source emptied
  MyVector: All tests passed!

=== ASSOCIATIVE CONTAINERS (ordered) ===
  [PASS] toSortedVector() – ascending order (BST in-order)
  [PASS] Move constructor: ownership transferred
  MySet: All tests passed!

=== SMART POINTERS ===
  [PASS] Move constructor: no ref-count change, source nulled
  [PASS] reset() – new pointer, previous ref count drops independently
  SharedPtr: All tests passed!

============================================
  ALL TESTS PASSED SUCCESSFULLY!
============================================
```

---

## Key Design Decisions

- **Templates in header + cpp**: implementation files are `#include`-d at the bottom of each header to keep declaration and definition in separate files while satisfying the template instantiation requirement.
- **BST for ordered containers**: `MySet` and `MyMap` use a plain (unbalanced) BST. Elements are always retrievable in sorted order via in-order traversal.
- **Separate chaining for hash containers**: each bucket is a `std::list<T>`, which handles collisions without probing. Rehashing doubles the bucket count automatically.
- **Adapter pattern**: `MyStack` and `MyQueue` delegate all storage to sequence containers, mirroring how the STL adapters work.
- **Reference counting for SharedPtr**: the reference count is heap-allocated and shared between all copies. Move operations transfer the pointer without touching the count.
