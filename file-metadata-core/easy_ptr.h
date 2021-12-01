#pragma once

template<typename T>
class EasyPtr
{
    T *ptr{nullptr};
    ulong size{0};

    EasyPtr(const EasyPtr<T> &) = delete;
    EasyPtr(EasyPtr<T> &&) = delete;
    EasyPtr<T> & operator= (const EasyPtr<T> &) = delete;
    EasyPtr<T> & operator= (EasyPtr<T> &&) = delete;

public:
    EasyPtr(ulong);

    EasyPtr();

    bool allocate(ulong);

    void free();

    bool validPos(ulong) const;

    ulong getSize() const;

    T * getPtr();

    const T * getPtr() const;

    const T * constPtr() const;

    T & operator[] (ulong);

    const T & operator[] (ulong) const;

    T & operator* ();

    const T & operator* () const;

    T * operator+ (ulong);

    const T * operator+ (ulong) const;

    operator bool () const;

    ~EasyPtr();
};

template<typename T>
EasyPtr<T>::EasyPtr(ulong sz)
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
bool EasyPtr<T>::allocate(ulong sz)
{
    if (!ptr && sz)
    {
        ptr = new(std::nothrow) T[sz];
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
    delete [] ptr;
    ptr = nullptr;
    size = 0;
}

template<typename T>
bool EasyPtr<T>::validPos(ulong pos) const
{
    return ptr && pos < size;
}

template<typename T>
ulong EasyPtr<T>::getSize() const
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
T & EasyPtr<T>::operator[] (ulong pos)
{
    return ptr[pos];
}

template<typename T>
const T & EasyPtr<T>::operator[] (ulong pos) const
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
T * EasyPtr<T>::operator+ (ulong offset)
{
    return ptr + offset;
}

template<typename T>
const T * EasyPtr<T>::operator+ (ulong offset) const
{
    return ptr + offset;
}

template<typename T>
EasyPtr<T>::operator bool () const
{
    return ptr;
}
