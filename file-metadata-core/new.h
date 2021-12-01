#pragma once
#include "pch.h"
#include "char_conversions.h"
using namespace std;

enum Byte_order {little_endian, big_endian, none};

enum String_encoding {iso_8859_1, ucs_2be, ucs_2le, utf_16be, utf_16le, utf_8, not_given};

enum Parsing_result {success, fail, no_id};

enum Tag_version {two, three, four, no_tag};

typedef bitset<8> mByte;

ulong kbyte(ulong k = 1)
{
    return k*1024;
}

ulong mbyte(ulong k = 1)
{
    return k*1024*1024;
}

long long power(long long, int);

QString get_genre(uchar);

template<typename T>
T my_min(T one, T two)
{
    if (one < two) {return one;}
    else {return two;}
}

template<typename T>
T my_max(T one, T two)
{
    if (one > two) {return one;}
    else {return two;}
}

ostream & operator << (ostream &, const QBitArray &);

ushort cut_ulong(ulong);//чекает, не превышает ли код символа 65 535

QByteArray qUncompressWrapper(const QByteArray &raw_data, ulong expected_size);

QByteArray qUncompressWrapper(QByteArray &&raw_data, ulong expected_size);
