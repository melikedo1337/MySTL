#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <utility>

// --- Sequence Containers ---
#include "sequence/MyVector.h"
#include "sequence/MyLinkedList.h"
#include "sequence/MyDeque.h"

// --- Associative Containers ---
#include "associative/MySet.h"
#include "associative/MyMap.h"

// --- Unordered Associative Containers ---
#include "unordered/MyUnorderedSet.h"
#include "unordered/MyUnorderedMap.h"

// --- Container Adapters ---
#include "adapters/MyStack.h"
#include "adapters/MyQueue.h"

// --- Smart Pointers ---
#include "smart_pointers/UniquePtr.h"
#include "smart_pointers/SharedPtr.h"

// --- Algorithms ---
#include "algorithms/Algorithms.h"

void printSection(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "========================================\n";
}
void printPass(const std::string& test) { std::cout << "  [PASS] " << test << "\n"; }

// ============================================================
// MyVector
// ============================================================
void testMyVector() {
    printSection("MyVector  [sequence]");

    MyVector<int> v;
    assert(v.empty() && v.size() == 0);
    printPass("Default constructor: empty");

    v.push_back(10); v.push_back(20); v.push_back(30);
    assert(v.size() == 3 && v[0] == 10 && v[2] == 30);
    assert(v.front() == 10 && v.back() == 30);
    printPass("push_back, operator[], front(), back()");

    v.pop_back();
    assert(v.size() == 2 && v.back() == 20);
    printPass("pop_back");

    try { v.at(99); assert(false); } catch (const std::out_of_range&) { printPass("at() throws out_of_range"); }

    // Copy
    MyVector<int> v2 = v;
    assert(v2.size() == v.size() && v2[0] == v[0]);
    printPass("Copy constructor");

    MyVector<int> v3;
    v3 = v;
    assert(v3[0] == v[0]);
    printPass("Copy assignment");

    // Move
    MyVector<int> v4 = std::move(v2);
    assert(v4.size() == 2 && v2.empty());
    printPass("Move constructor: ownership transferred, source emptied");

    MyVector<int> v5;
    v5 = std::move(v4);
    assert(v5.size() == 2 && v4.empty());
    printPass("Move assignment: ownership transferred, source emptied");

    v.clear();
    assert(v.empty());
    printPass("clear()");

    std::cout << "  MyVector: All tests passed!\n";
}

// ============================================================
// MyLinkedList
// ============================================================
void testMyLinkedList() {
    printSection("MyLinkedList  [sequence]");

    MyLinkedList<int> list;
    assert(list.empty());
    printPass("Default constructor: empty");

    list.push_back(1); list.push_back(2); list.push_back(3);
    list.push_front(0);
    assert(list.size() == 4 && list.front() == 0 && list.back() == 3);
    printPass("push_front, push_back, front(), back()");

    std::cout << "  List: "; list.print();

    list.pop_front(); assert(list.front() == 1);
    list.pop_back();  assert(list.back() == 2);
    printPass("pop_front, pop_back");

    assert(list.contains(1) && !list.contains(99));
    printPass("contains()");

    list.push_back(1); list.push_back(1);
    list.remove(1);
    assert(!list.contains(1));
    printPass("remove() removes all occurrences");

    // Copy
    MyLinkedList<int> l2 = list;
    assert(l2.size() == list.size());
    printPass("Copy constructor");

    // Move
    MyLinkedList<int> l3 = std::move(l2);
    assert(l3.size() > 0 && l2.empty());
    printPass("Move constructor: ownership transferred");

    MyLinkedList<int> l4;
    l4 = std::move(l3);
    assert(l4.size() > 0 && l3.empty());
    printPass("Move assignment: ownership transferred");

    list.clear(); assert(list.empty());
    printPass("clear()");

    std::cout << "  MyLinkedList: All tests passed!\n";
}

// ============================================================
// MyDeque
// ============================================================
void testMyDeque() {
    printSection("MyDeque  [sequence]");

    MyDeque<int> d;
    assert(d.empty());
    printPass("Default constructor: empty");

    d.push_back(10); d.push_back(20);
    d.push_front(5); d.push_front(1);
    assert(d.size() == 4 && d.front() == 1 && d.back() == 20);
    assert(d[0] == 1 && d[1] == 5 && d[2] == 10 && d[3] == 20);
    printPass("push_front, push_back, front(), back(), operator[]");

    d.pop_front(); assert(d.front() == 5);
    d.pop_back();  assert(d.back() == 10);
    printPass("pop_front, pop_back");

    try { d.at(100); assert(false); } catch (const std::out_of_range&) { printPass("at() throws out_of_range"); }

    // Copy
    MyDeque<int> d2 = d;
    assert(d2.size() == d.size() && d2.front() == d.front());
    printPass("Copy constructor");

    // Move
    MyDeque<int> d3 = std::move(d2);
    assert(d3.size() > 0 && d2.empty());
    printPass("Move constructor: ownership transferred");

    MyDeque<int> d4;
    d4 = std::move(d3);
    assert(d4.size() > 0 && d3.empty());
    printPass("Move assignment: ownership transferred");

    d.clear(); assert(d.empty());
    printPass("clear()");

    std::cout << "  MyDeque: All tests passed!\n";
}

// ============================================================
// MySet
// ============================================================
void testMySet() {
    printSection("MySet  [associative / ordered BST]");

    MySet<int> s;
    assert(s.empty());
    printPass("Default constructor: empty");

    assert(s.insert(5) && s.insert(3) && s.insert(7) && s.insert(1));
    assert(!s.insert(5));
    assert(s.size() == 4);
    printPass("insert() – unique elements only, duplicate returns false");

    assert(s.contains(3) && !s.contains(99));
    printPass("contains()");

    auto sv = s.toSortedVector();
    for (size_t i = 1; i < sv.size(); ++i) assert(sv[i] > sv[i-1]);
    printPass("toSortedVector() – ascending order (BST in-order)");

    assert(s.erase(3) && !s.contains(3) && !s.erase(99));
    printPass("erase()");

    // Copy
    MySet<int> s2 = s;
    assert(s2.size() == s.size() && s2.contains(5));
    printPass("Copy constructor");

    // Move
    MySet<int> s3 = std::move(s2);
    assert(s3.size() > 0 && s2.empty());
    printPass("Move constructor: ownership transferred");

    MySet<int> s4;
    s4 = std::move(s3);
    assert(s4.size() > 0 && s3.empty());
    printPass("Move assignment: ownership transferred");

    MySet<std::string> ss;
    ss.insert("banana"); ss.insert("apple"); ss.insert("cherry");
    auto ssv = ss.toSortedVector();
    assert(ssv[0]=="apple" && ssv[1]=="banana" && ssv[2]=="cherry");
    printPass("Works with std::string, sorted correctly");

    s.clear(); assert(s.empty());
    printPass("clear()");

    std::cout << "  MySet: All tests passed!\n";
}

// ============================================================
// MyMap
// ============================================================
void testMyMap() {
    printSection("MyMap  [associative / ordered BST]");

    MyMap<std::string, int> m;
    assert(m.empty());
    printPass("Default constructor: empty");

    assert(m.insert("alice", 90) && m.insert("bob", 75) && m.insert("carol", 88));
    assert(!m.insert("alice", 99));
    assert(m.size() == 3);
    printPass("insert() – unique keys only, duplicate returns false");

    assert(m.contains("alice") && !m.contains("dave"));
    printPass("contains()");

    assert(m.at("alice") == 90 && m.at("bob") == 75);
    try { m.at("dave"); assert(false); } catch (const std::out_of_range&) { printPass("at() throws out_of_range for missing key"); }

    m["alice"] = 100; assert(m.at("alice") == 100);
    m["dave"]  = 55;  assert(m.contains("dave") && m.at("dave") == 55);
    printPass("operator[] – update existing and insert new");

    auto sv = m.toSortedVector();
    for (size_t i = 1; i < sv.size(); ++i) assert(sv[i].first > sv[i-1].first);
    printPass("toSortedVector() – sorted by key");

    assert(m.erase("bob") && !m.contains("bob") && !m.erase("nobody"));
    printPass("erase()");

    // Copy
    MyMap<std::string, int> m2 = m;
    assert(m2.size() == m.size());
    printPass("Copy constructor");

    // Move
    MyMap<std::string, int> m3 = std::move(m2);
    assert(m3.size() > 0 && m2.empty());
    printPass("Move constructor: ownership transferred");

    MyMap<std::string, int> m4;
    m4 = std::move(m3);
    assert(m4.size() > 0 && m3.empty());
    printPass("Move assignment: ownership transferred");

    m.clear(); assert(m.empty());
    printPass("clear()");

    std::cout << "  MyMap: All tests passed!\n";
}

// ============================================================
// MyUnorderedSet
// ============================================================
void testMyUnorderedSet() {
    printSection("MyUnorderedSet  [unordered associative / hash table]");

    MyUnorderedSet<int> us;
    assert(us.empty());
    printPass("Default constructor: empty");

    assert(us.insert(10) && us.insert(20) && us.insert(30));
    assert(!us.insert(10));
    assert(us.size() == 3);
    printPass("insert() – unique elements, duplicate returns false");

    assert(us.contains(20) && !us.contains(99));
    printPass("contains()");

    assert(us.erase(20) && !us.contains(20) && !us.erase(99));
    printPass("erase()");

    for (int i = 0; i < 100; ++i) us.insert(i);
    assert(us.size() == 100);
    printPass("100 insertions with rehashing");

    // Copy
    MyUnorderedSet<int> us2 = us;
    assert(us2.size() == us.size());
    printPass("Copy constructor");

    // Move
    MyUnorderedSet<int> us3 = std::move(us2);
    assert(us3.size() == 100 && us2.empty());
    printPass("Move constructor: ownership transferred");

    MyUnorderedSet<int> us4;
    us4 = std::move(us3);
    assert(us4.size() == 100 && us3.empty());
    printPass("Move assignment: ownership transferred");

    us.clear(); assert(us.empty());
    printPass("clear()");

    std::cout << "  MyUnorderedSet: All tests passed!\n";
}

// ============================================================
// MyUnorderedMap
// ============================================================
void testMyUnorderedMap() {
    printSection("MyUnorderedMap  [unordered associative / hash table]");

    MyUnorderedMap<std::string, int> um;
    assert(um.empty());
    printPass("Default constructor: empty");

    assert(um.insert("x", 1) && um.insert("y", 2) && um.insert("z", 3));
    assert(!um.insert("x", 9));
    assert(um.size() == 3);
    printPass("insert() – unique keys, duplicate returns false");

    assert(um.contains("y") && !um.contains("w"));
    printPass("contains()");

    assert(um.at("x") == 1 && um.at("z") == 3);
    try { um.at("missing"); assert(false); } catch (const std::out_of_range&) { printPass("at() throws out_of_range for missing key"); }

    um["x"] = 42; assert(um.at("x") == 42);
    um["new"] = 99; assert(um.contains("new") && um.at("new") == 99);
    printPass("operator[] – update existing and insert new");

    assert(um.erase("y") && !um.contains("y") && !um.erase("nobody"));
    printPass("erase()");

    MyUnorderedMap<int, int> big;
    for (int i = 0; i < 100; ++i) big.insert(i, i * i);
    assert(big.size() == 100);
    for (int i = 0; i < 100; ++i) assert(big.at(i) == i * i);
    printPass("100 insertions with rehashing, all lookups correct");

    // Copy
    MyUnorderedMap<std::string, int> um2 = um;
    assert(um2.size() == um.size());
    printPass("Copy constructor");

    // Move
    MyUnorderedMap<std::string, int> um3 = std::move(um2);
    assert(um3.size() > 0 && um2.empty());
    printPass("Move constructor: ownership transferred");

    MyUnorderedMap<std::string, int> um4;
    um4 = std::move(um3);
    assert(um4.size() > 0 && um3.empty());
    printPass("Move assignment: ownership transferred");

    um.clear(); assert(um.empty());
    printPass("clear()");

    std::cout << "  MyUnorderedMap: All tests passed!\n";
}

// ============================================================
// MyStack
// ============================================================
void testMyStack() {
    printSection("MyStack  [adapter over MyVector]");

    MyStack<int> s;
    assert(s.empty());
    printPass("Default constructor: empty");

    s.push(10); s.push(20); s.push(30);
    assert(s.size() == 3 && s.top() == 30);
    printPass("push(), top()");

    s.pop(); assert(s.top() == 20);
    printPass("pop()");

    try { MyStack<int> e; e.pop(); assert(false); } catch (const std::underflow_error&) { printPass("pop() throws underflow_error on empty"); }

    // Copy
    MyStack<int> s2 = s;
    assert(s2.size() == s.size() && s2.top() == s.top());
    printPass("Copy constructor");

    // Move
    MyStack<int> s3 = std::move(s2);
    assert(s3.size() > 0 && s2.empty());
    printPass("Move constructor: ownership transferred");

    MyStack<int> s4;
    s4 = std::move(s3);
    assert(s4.size() > 0 && s3.empty());
    printPass("Move assignment: ownership transferred");

    s.clear(); assert(s.empty());
    printPass("clear()");

    std::cout << "  MyStack: All tests passed!\n";
}

// ============================================================
// MyQueue
// ============================================================
void testMyQueue() {
    printSection("MyQueue  [adapter over MyLinkedList]");

    MyQueue<int> q;
    assert(q.empty());
    printPass("Default constructor: empty");

    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    assert(q.size() == 3 && q.front() == 1 && q.back() == 3);
    printPass("enqueue(), front(), back()");

    q.dequeue(); assert(q.front() == 2 && q.size() == 2);
    printPass("dequeue() – FIFO order");

    try { MyQueue<int> e; e.dequeue(); assert(false); } catch (const std::underflow_error&) { printPass("dequeue() throws underflow_error on empty"); }

    // Copy
    MyQueue<int> q2 = q;
    assert(q2.size() == q.size() && q2.front() == q.front());
    printPass("Copy constructor");

    // Move
    MyQueue<int> q3 = std::move(q2);
    assert(q3.size() > 0 && q2.empty());
    printPass("Move constructor: ownership transferred");

    MyQueue<int> q4;
    q4 = std::move(q3);
    assert(q4.size() > 0 && q3.empty());
    printPass("Move assignment: ownership transferred");

    q.clear(); assert(q.empty());
    printPass("clear()");

    std::cout << "  MyQueue: All tests passed!\n";
}

// ============================================================
// UniquePtr
// ============================================================
void testUniquePtr() {
    printSection("UniquePtr  [smart pointers]");

    UniquePtr<int> p(new int(42));
    assert(p && *p == 42);
    printPass("Constructor and dereference");

    UniquePtr<int> p2 = std::move(p);
    assert(!p && *p2 == 42);
    printPass("Move constructor: ownership transferred");

    UniquePtr<int> p3;
    p3 = std::move(p2);
    assert(!p2 && *p3 == 42);
    printPass("Move assignment: ownership transferred");

    int* raw = p3.release();
    assert(!p3 && *raw == 42);
    delete raw;
    printPass("release() – nulls UniquePtr, returns raw pointer");

    UniquePtr<int> p4(new int(10));
    p4.reset(new int(99));
    assert(*p4 == 99);
    p4.reset();
    assert(!p4);
    printPass("reset() – replaces or nulls pointer");

    struct P { int x, y; };
    UniquePtr<P> pp(new P{3, 4});
    assert(pp->x == 3 && pp->y == 4);
    printPass("operator-> on struct");

    std::cout << "  UniquePtr: All tests passed!\n";
}

// ============================================================
// SharedPtr
// ============================================================
void testSharedPtr() {
    printSection("SharedPtr  [smart pointers]");

    SharedPtr<int> sp1(new int(100));
    assert(sp1 && *sp1 == 100 && sp1.use_count() == 1);
    printPass("Constructor, dereference, use_count(1)");

    SharedPtr<int> sp2 = sp1;
    assert(sp1.use_count() == 2 && sp2.use_count() == 2);
    printPass("Copy constructor increments ref count to 2");

    {
        SharedPtr<int> sp3 = sp1;
        assert(sp1.use_count() == 3);
        printPass("Nested copy: ref count = 3");
    }
    assert(sp1.use_count() == 2);
    printPass("Destructor decrements ref count back to 2");

    SharedPtr<int> sp4 = std::move(sp2);
    assert(!sp2 && sp4.use_count() == 2);
    printPass("Move constructor: no ref-count change, source nulled");

    SharedPtr<int> sp5;
    sp5 = std::move(sp4);
    assert(!sp4 && sp5.use_count() == 2);
    printPass("Move assignment: no ref-count change, source nulled");

    sp1.reset(new int(200));
    assert(*sp1 == 200 && sp1.use_count() == 1 && sp5.use_count() == 1);
    printPass("reset() – new pointer, previous ref count drops independently");

    SharedPtr<int> null_sp;
    assert(!null_sp && null_sp.use_count() == 0);
    printPass("Default-constructed SharedPtr is null, use_count = 0");

    struct P { int x, y; };
    SharedPtr<P> psp(new P{7, 8});
    assert(psp->x == 7 && psp->y == 8);
    printPass("operator-> on struct");

    std::cout << "  SharedPtr: All tests passed!\n";
}

// ============================================================
// Algorithms
// ============================================================
void printVec(const std::string& label, const std::vector<int>& v) {
    std::cout << "  " << label << ": [";
    for (size_t i = 0; i < v.size(); ++i) { std::cout << v[i]; if (i+1<v.size()) std::cout << ", "; }
    std::cout << "]\n";
}

void testAlgorithms() {
    printSection("Algorithms");

    auto check = [](std::vector<int> v) { return MyAlgorithms::isSorted(v); };

    std::vector<int> a1 = {64,34,25,12,22,11,90};
    printVec("Before bubbleSort", a1);
    MyAlgorithms::bubbleSort(a1); printVec("After ", a1);
    assert(check(a1)); printPass("bubbleSort");

    std::vector<int> a2 = {29,10,14,37,13};
    MyAlgorithms::selectionSort(a2); assert(check(a2)); printPass("selectionSort");

    std::vector<int> a3 = {5,2,8,1,9,3};
    MyAlgorithms::insertionSort(a3); assert(check(a3)); printPass("insertionSort");

    std::vector<int> a4 = {38,27,43,3,9,82,10};
    MyAlgorithms::mergeSort(a4, 0, (int)a4.size()-1); assert(check(a4)); printPass("mergeSort");

    std::vector<int> a5 = {10,7,8,9,1,5};
    MyAlgorithms::quickSort(a5, 0, (int)a5.size()-1); assert(check(a5)); printPass("quickSort");

    std::vector<int> data = {4,2,7,1,9,3};
    assert(MyAlgorithms::linearSearch(data, 7) == 2);
    assert(MyAlgorithms::linearSearch(data, 99) == -1);
    printPass("linearSearch");

    std::vector<int> sorted = {1,3,5,7,9,11,13};
    assert(MyAlgorithms::binarySearch(sorted, 7) == 3);
    assert(MyAlgorithms::binarySearch(sorted, 6) == -1);
    printPass("binarySearch");

    std::vector<int> vals = {3,1,4,1,5,9,2,6};
    assert(MyAlgorithms::findMin(vals) == 1 && MyAlgorithms::findMax(vals) == 9);
    printPass("findMin, findMax");

    std::vector<int> rev = {1,2,3,4,5};
    MyAlgorithms::reverseArray(rev);
    assert(rev[0]==5 && rev[4]==1);
    printPass("reverseArray");

    assert(MyAlgorithms::isSorted(std::vector<int>{1,2,3}) == true);
    assert(MyAlgorithms::isSorted(std::vector<int>{1,3,2}) == false);
    printPass("isSorted");

    std::cout << "  Algorithms: All tests passed!\n";
}

// ============================================================
// Main
// ============================================================
int main() {
    std::cout << "\n############################################\n";
    std::cout << "#   STL Implementation Test Suite          #\n";
    std::cout << "############################################\n";

    std::cout << "\n=== SEQUENCE CONTAINERS ===";
    testMyVector();
    testMyLinkedList();
    testMyDeque();

    std::cout << "\n=== ASSOCIATIVE CONTAINERS (ordered) ===";
    testMySet();
    testMyMap();

    std::cout << "\n=== UNORDERED ASSOCIATIVE CONTAINERS ===";
    testMyUnorderedSet();
    testMyUnorderedMap();

    std::cout << "\n=== CONTAINER ADAPTERS ===";
    testMyStack();
    testMyQueue();

    std::cout << "\n=== SMART POINTERS ===";
    testUniquePtr();
    testSharedPtr();

    std::cout << "\n=== ALGORITHMS ===";
    testAlgorithms();

    std::cout << "\n============================================\n";
    std::cout << "  ALL TESTS PASSED SUCCESSFULLY!\n";
    std::cout << "============================================\n\n";

    return 0;
}
