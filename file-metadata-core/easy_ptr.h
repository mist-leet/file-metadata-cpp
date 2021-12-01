#pragma once
#include "new.h"
using namespace std;

template<typename T>
class EasyPtr
{
    T *ptr{nullptr};
    uint size{0};

    EasyPtr(const EasyPtr<T> &) = delete;
    EasyPtr(EasyPtr<T> &&) = delete;
    EasyPtr<T> & operator= (const EasyPtr<T> &) = delete;
    EasyPtr<T> & operator= (EasyPtr<T> &&) = delete;

public:
    EasyPtr(uint);

    EasyPtr();

    bool allocate(uint);

    void free();

    bool validPos(uint) const;

    uint getSize() const;

    T * getPtr();

    const T * getPtr() const;

    const T * constPtr() const;

    T & operator[] (uint);

    const T & operator[] (uint) const;

    T & operator* ();

    const T & operator* () const;

    T * operator+ (uint);

    const T * operator+ (uint) const;

    operator bool () const;

    ~EasyPtr();
};

template<typename T>
EasyPtr<T>::EasyPtr(uint sz)
{
    allocate(sz);
}

template<typename T>
EasyPtr<T>::EasyPtr() {}

template<typename T>
EasyPtr<T>::~EasyPtr()
{
    free();
}

template<typename T>
bool EasyPtr<T>::allocate(uint sz)
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
void EasyPtr<T>::free()
{
    if (ptr) {delete [] ptr;}
    ptr = nullptr;
    size = 0;
}

template<typename T>
bool EasyPtr<T>::validPos(uint pos) const
{
    return ptr && pos < size;
}

template<typename T>
uint EasyPtr<T>::getSize() const
{
    return size;
}

template<typename T>
const T * EasyPtr<T>::getPtr() const
{
    return ptr;
}

template<typename T>
T * EasyPtr<T>::getPtr()
{
    return ptr;
}

template<typename T>
const T * EasyPtr<T>::constPtr() const
{
    return ptr;
}

template<typename T>
T & EasyPtr<T>::operator[] (uint pos)
{
    return ptr[pos];
}

template<typename T>
const T & EasyPtr<T>::operator[] (uint pos) const
{
    return ptr[pos];
}

template<typename T>
T & EasyPtr<T>::operator* ()
{
    return *ptr;
}

template<typename T>
const T & EasyPtr<T>::operator* () const
{
    return *ptr;
}

template<typename T>
T * EasyPtr<T>::operator+ (uint offset)
{
    return ptr + offset;
}

template<typename T>
const T * EasyPtr<T>::operator+ (uint offset) const
{
    return ptr + offset;
}

template<typename T>
EasyPtr<T>::operator bool () const
{
    return ptr;
}
