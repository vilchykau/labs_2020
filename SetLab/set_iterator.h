#pragma once

#include <iterator>

template <typename T>
class set_iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = int;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    

    set_iterator(value_type* p) : p(p) {}

    value_type& operator*() const
    {
        return *p;
    }
    set_iterator operator++(int);
    set_iterator operator++();
    auto operator-(const set_iterator& other) const;
    set_iterator operator--(int);
    set_iterator operator--();
    bool operator==(const set_iterator& other) const;
    bool operator!=(const set_iterator& other) const;

    bool operator<(const set_iterator& other) const {
        return p < other.p;
    }
    bool operator<=(const set_iterator& other) const {
        return p <= other.p;
    }
    bool operator>(const set_iterator& other) const {
        return p > other.p;
    }
    bool operator>=(const set_iterator& other) const {
        return p >= other.p;
    }

    set_iterator operator+(int steps) const{
        return set_iterator(p + steps);
    }

    set_iterator operator-(int steps) const {
        return set_iterator(p - steps);
    }

private:
    value_type* p;
};

template <typename T>
set_iterator<T> set_iterator<T>::operator++(int)
{
    p++;
    return p;
}

template <typename T>
set_iterator<T> set_iterator<T>::operator++()
{
    set_iterator temp(p);
    p++;
    return temp;
}

template <typename T>
auto set_iterator<T>::operator-(const set_iterator& other) const
{
    return (difference_type)(p - other.p);
}

template <typename T>
set_iterator<T> set_iterator<T>::operator--(int)
{
    p--;
    return p;
}

template <typename T>
set_iterator<T> set_iterator<T>::operator--()
{
    set_iterator temp(p);
    p--;
    return temp;
}

template <typename T>
bool set_iterator<T>::operator==(const set_iterator& other) const
{
    return p == other.p;
}

template <typename T>
bool set_iterator<T>::operator!=(const set_iterator& other) const
{
    return p != other.p;
}