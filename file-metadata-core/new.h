#pragma once
#include "global_constants.h"
#include "easy_ptr.h"

long long power(long long, int);

ulong kbyte(ulong k = 1);

ulong mbyte(ulong k = 1);

QString getGenre(uchar);

template<typename T>
T my_min(T one, T two)
{
    if (one < two) {return one;}
    else {return two;}
}

template<typename T, class = std::enable_if_t<anyChar<T>>>
T my_max(T one, T two)
{
    if (one > two) {return one;}
    else {return two;}
}

std::vector<uchar> uncompressWrapper(const std::vector<uchar> &, ulong);
