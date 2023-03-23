// *****************************************************************************
// SmallList.hpp:
// *****************************************************************************
#pragma once
#pragma warning(disable: 26400 26401 26402 26408 26409)
#pragma warning(disable: 26426 26429 26432 26440 26455 26461 26462)
#pragma warning(disable: 26481 26485 26493 26496 26497)
#pragma warning(disable: 6386 6387)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cfloat>
#include <utility>
#include <algorithm>

// Stores a random-access sequence of elements similar to vector, but avoids
// heap allocations for small lists. T must be trivially constructible and
// destructible.
template <class T>
class SmallList
{
public:
    // Creates an empty list.
    SmallList();

    // Creates a copy of the specified list.
    SmallList(const SmallList& other);

    // Copies the specified list.
    SmallList& operator=(const SmallList& other);

    // Destroys the list.
    ~SmallList();

    // Returns the number of agents in the list.
    int size() const;

    // Returns the nth element.
    T& operator[](int n);

    // Returns the nth element in the list.
    const T& operator[](int n) const;

    // Returns an index to a matching element in the list or -1
    // if the element is not found.
    int find_index(const T& element) const;

    // Clears the list.
    void clear();

    // Reserves space for n elements.
    void reserve(int n);

    // Inserts an element to the back of the list.
    void push_back(const T& element);

    /// Pops an element off the back of the list.
    T pop_back();

    // Swaps the contents of this list with the other.
    void swap(SmallList& other);

    // Returns a pointer to the underlying buffer.
    T* data();

    // Returns a pointer to the underlying buffer.
    const T* data() const;

private:
    enum { fixed_cap = 256 };
    struct ListData {
        ListData();
        T buf[fixed_cap]{};
        T* data{};
        int num{};
        int cap{};
    };
    ListData ld;
};


// ---------------------------------------------------------------------------------
// SmallList Implementation
// ---------------------------------------------------------------------------------
template <class T>
SmallList<T>::ListData::ListData(): data(buf), num(0), cap(fixed_cap) {
}

template <class T>
SmallList<T>::SmallList() {
}

template <class T>
SmallList<T>::SmallList(const SmallList& other)
{
    if (other.ld.cap == fixed_cap) {
        ld = other.ld;
        ld.data = ld.buf;
    } else {
        reserve(other.ld.num);
        for (int j = 0; j < other.size(); ++j) {
            ld.data[j] = other.ld.data[j];
        }
        ld.num = other.ld.num;
        ld.cap = other.ld.cap;
    }
}

template <class T>
SmallList<T>& SmallList<T>::operator=(const SmallList<T>& other) {
    SmallList(other).swap(*this);
    return *this;
}

template <class T>
SmallList<T>::~SmallList() {
    if (ld.data != ld.buf) {
        free(ld.data);
    }
}

template <class T>
int SmallList<T>::size() const {
    return ld.num;
}

template <class T>
T& SmallList<T>::operator[](int n) {
    assert(n >= 0 && n < ld.num);
    return ld.data[n];
}

template <class T>
const T& SmallList<T>::operator[](int n) const {
    assert(n >= 0 && n < ld.num);
    return ld.data[n];
}

template <class T>
int SmallList<T>::find_index(const T& element) const {
    for (int j = 0; j < ld.num; ++j) {
        if (ld.data[j] == element) {
            return j;
        }
    }
    return -1;
}

template <class T>
void SmallList<T>::clear() {
    ld.num = 0;
}

template <class T>
void SmallList<T>::reserve(int n) {
    enum { type_size = sizeof(T) };
    if (n > ld.cap) {
        if (ld.cap == fixed_cap) {
            assert(n > fixed_cap);
            ld.data = static_cast<T*>(malloc((long long)n * type_size));
            assert(ld.data != nullptr);
            memcpy(ld.data, ld.buf, sizeof(ld.buf));
        } else {
            T* temp = static_cast<T*>(realloc(ld.data, (long long)n * type_size));
            assert(temp != nullptr);
            ld.data = temp;
        }
        ld.cap = n;
    }
}

template <class T>
void SmallList<T>::push_back(const T& element) {
    if (ld.num >= ld.cap) {
        reserve(ld.cap * 2);
    }
    ld.data[ld.num++] = element;
}

template <class T>
T SmallList<T>::pop_back() {
    return ld.data[--ld.num];
}

template <class T>
void SmallList<T>::swap(SmallList& other) {
    ListData& ld1 = ld;
    ListData& ld2 = other.ld;

    const int use_fixed1 = ld1.data == ld1.buf;
    const int use_fixed2 = ld2.data == ld2.buf;

    const ListData temp = ld1;
    ld1 = ld2;
    ld2 = temp;

    if (use_fixed1) {
        ld2.data = ld2.buf;
    }
    if (use_fixed2) {
        ld1.data = ld1.buf;
    }
}

template <class T>
T* SmallList<T>::data() {
    return ld.data;
}

template <class T>
const T* SmallList<T>::data() const {
    return ld.data;
}