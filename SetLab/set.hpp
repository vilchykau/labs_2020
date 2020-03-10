#pragma once

#include <list>
#include <iostream>

#include "set_iterator.h"

template <typename T>
class Set
{
public:
    using value_type = T;
    using iterator = set_iterator<T>;
    using const_iterator = iterator;
    using size_type = size_t;

    Set() : a(new value_type[0]),
        size(0),
        capacity(0)
    {
    }

    template <typename Iterator>
    Set(Iterator first, Iterator last) : Set()
    {
        while (first != last)
        {
            insert(*first);
        }
    }

    Set(std::initializer_list<value_type> list) : Set()
    {
        for (const auto& i : list)
        {
            insert(i);
        }
    }

    Set(const Set& other);
    Set(Set&& other);
    Set& operator=(const Set& other);
    Set& operator=(Set&& other);
    ~Set() { delete[] a; }

    auto insert(const value_type& value);

    template <typename... Args>
    void emplace(value_type value, Args... args);
    void emplace() {}
    template <typename... Args>
    void emplace_hint(const_iterator it, value_type value, Args... args);

    void swap(Set& other);

    auto begin() const;
    auto end() const;

    auto find(const value_type& value) const;
    auto insert(iterator it, const value_type& value);
    void clear();

    iterator erase(iterator start_range, iterator end_range) {
        auto diff = end_range - start_range;
        if (diff > 0) {
            size_t new_size = size - diff;
            iterator s = begin();
            iterator e = end();
            value_type* new_array = new value_type[new_size];
            size_t pos = 0;
            while (s != e)
            {
                if (s < start_range || s >= end_range) {
                    new_array[pos] = *s;
                    ++pos;
                }
                ++s;
            }
            delete a;
            a = new_array;
            size = new_size;
            return begin();
        }
        else {
            return begin();
        }
    }

    iterator erase(iterator pos) {
        return erase(pos, pos + 1);
    }

    size_type erase(const value_type& value) {
        auto it = find(value);
        if (it != end()) {
            erase(it);
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator==(const Set& other) const {
        if (this == &other) {
            return true;
        }
        else if (other.size != size) {
            return false;
        }
        else {
            auto s1 = begin();
            auto s2 = other.begin();
            auto e1 = end();
            auto e2 = other.end();

            while (s1 != e1) {
                if (!are_equal(*s1, *s2)) {
                    return false;
                }
                ++s1;
                ++s2;
            }
            return true;
        }
    }

    bool operator!=(const Set& other) const {
        return !(*this == other);
    }

private:
    bool are_equal(const value_type& first, const value_type& second) const {
        if (first < second || second < first) {
            return false;
        }
        return true;
    }

    auto find(size_t start, size_t end, const value_type& value) const;

    value_type* a;
    size_t size;
    size_t capacity;
};

template <typename T>
Set<T>::Set(const Set& other)
{
    a = new value_type[other.size];
    size = other.size;
    capacity = other.capacity;

    for (size_t i = 0; i < size; ++i)
    {
        a[i] = other.a[i];
    }
}

template <typename T>
Set<T>::Set(Set&& other) : Set()
{
    swap(other);
}

template <typename T>
Set<T>& Set<T>::operator=(const Set& other)
{
    if (&other != this)
    {
        Set temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
auto Set<T>::insert(const value_type& value)
{
    auto find_it = find(value);
    if (find_it == end())
    {
        const size_t new_size = size + 1;
        value_type* new_array = new value_type[new_size];
        size_t i = 0;
        for (; i < size && a[i] < value; ++i)
        {
            new_array[i] = a[i];
        }
        new_array[i] = value;
        auto element_index = i;
        for (; i < size + 1; ++i)
        {
            new_array[i + 1] = a[i];
        }
        delete[] a;
        a = new_array;
        size += 1;
        return iterator(&a[element_index]);
    }
    else {
        return find_it;
    }
}

template <typename T>
Set<T>& Set<T>::operator=(Set&& other)
{
    if (&other != this)
    {
        Set temp;
        temp.swap(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
template <typename... Args>
void Set<T>::emplace(value_type value, Args... args)
{
    insert(value);
    emplace(args...);
}

template <typename T>
template <typename... Args>
void Set<T>::emplace_hint(const_iterator it, value_type value, Args... args)
{
    emplace(value, args...);
}

template <typename T>
void Set<T>::swap(Set<T>& other)
{
    std::swap(a, other.a);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}

template <typename T>
auto Set<T>::begin() const
{
    return iterator(a);
}
template <typename T>
auto Set<T>::end() const
{
    return iterator(a + size);
}

template <typename T>
auto Set<T>::find(const value_type& value) const
{
    return find(0, size, value);
}

template <typename T>
auto Set<T>::insert(iterator it, const value_type& value)
{
    return insert(value);
}

template <typename T>
auto Set<T>::find(size_t start, size_t end, const value_type& value) const
{
    while (start < end)
    {
        auto mid = (start + end + 1) / 2;
        if (value < a[mid])
        {
            end = mid - 1;
        }
        else if(a[mid] < value)
        {
            start = mid;
        }
        else {
            return iterator(a + mid);
        }
    }
    return value == a[start] ? iterator(a + start) : iterator(a + size);
}

template<typename T>
void Set<T>::clear() {
    Set temp;
    swap(temp);
}
/*
std::for_each(c.begin(), e.end(), [](const auto& vlaue){
    std::cout << vlaue;
});*/

