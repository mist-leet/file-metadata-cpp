#pragma once
#include "new.h"
using namespace std;

template<typename T>
class Easy_ptr
{
    T *ptr{nullptr};
    uint size{0};

    Easy_ptr(const Easy_ptr<T> &) = delete;
    Easy_ptr(Easy_ptr<T> &&) = delete;
    Easy_ptr<T> & operator= (const Easy_ptr<T> &) = delete;
    Easy_ptr<T> & operator= (Easy_ptr<T> &&) = delete;

public:
    Easy_ptr(uint);

    Easy_ptr();

    bool allocate(uint);

    void free();

    bool valid_pos(uint) const;

    uint get_size() const;

    T * get_ptr();

    const T * get_ptr() const;

    const T * const_ptr() const;

    T & operator[] (uint);

    const T & operator[] (uint) const;

    T & operator* ();

    const T & operator* () const;

    T * operator+ (uint);

    const T * operator+ (uint) const;

    operator bool () const;

    ~Easy_ptr();
};

template<typename T>
Easy_ptr<T>::Easy_ptr(uint sz)
{
    allocate(sz);
}

template<typename T>
Easy_ptr<T>::Easy_ptr() {}

template<typename T>
Easy_ptr<T>::~Easy_ptr()
{
    free();
}

template<typename T>
bool Easy_ptr<T>::allocate(uint sz)
{
    if (!ptr && sz)
    {
        ptr = new(nothrow) T[sz];
        if (ptr)
            size = sz;
        return ptr;
    }
    else
        return false;
}

template<typename T>
void Easy_ptr<T>::free()
{
    if (ptr) {delete [] ptr;}
    ptr = nullptr;
    size = 0;
}

template<typename T>
bool Easy_ptr<T>::valid_pos(uint pos) const
{
    return ptr && pos < size;
}

template<typename T>
uint Easy_ptr<T>::get_size() const
{
    return size;
}

template<typename T>
const T * Easy_ptr<T>::get_ptr() const
{
    return ptr;
}

template<typename T>
T * Easy_ptr<T>::get_ptr()
{
    return ptr;
}

template<typename T>
const T * Easy_ptr<T>::const_ptr() const
{
    return ptr;
}

template<typename T>
T & Easy_ptr<T>::operator[] (uint pos)
{
    return ptr[pos];
}

template<typename T>
const T & Easy_ptr<T>::operator[] (uint pos) const
{
    return ptr[pos];
}

template<typename T>
T & Easy_ptr<T>::operator* ()
{
    return *ptr;
}

template<typename T>
const T & Easy_ptr<T>::operator* () const
{
    return *ptr;
}

template<typename T>
T * Easy_ptr<T>::operator+ (uint offset)
{
    return ptr + offset;
}

template<typename T>
const T * Easy_ptr<T>::operator+ (uint offset) const
{
    return ptr + offset;
}

template<typename T>
Easy_ptr<T>::operator bool () const
{
    return ptr;
}
