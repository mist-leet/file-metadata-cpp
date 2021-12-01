#pragma once
#include "char_conversions.h"
#include <functional>
using namespace std;
/*
 * bool getChar(char *);//достаёт char из файла/структуры и кладёт по указанному адресу
 */

//чтение символов с инкрементацией счётчика

template<typename T>//getting char & incrementing count
char ch(function<bool(char *)> getChar, T &count);

template<typename T>//getting uchar & incrementing count
uchar get(function<bool(char *)> getChar, T &count);

template<typename T>//getting char w/ unsynch & incrementing count
char uch(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting uchar w/ unsynch & incrementing count
uchar getb(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting utf8-encoded unicode symbol & incrementing count
ulong get_utf8(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting utf16-encoded unicode symbol & incrementing count
ulong get_utf16(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting ucs2-encoded unicode symbol & incrementing count
ushort get_ucs2(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting BOM & incrementing count
Byte_order get_BOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

//чтение символов без инкрементации счётчика

//getting char
char ch(function<bool(char *)> getChar);

//getting uchar
uchar get(function<bool(char *)> getChar);

//getting char w/ unsynch
char uch(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//getting uchar w/ unsynch
uchar getb(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//getting utf8-encoded unicode symbol
ulong get_utf8(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//getting utf16-encoded unicode symbol
ulong get_utf16(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back);

//getting ucs2-encoded unicode symbol
ushort get_ucs2(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back);

//getting BOM
Byte_order get_BOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//чтение строк в разных кодировках с учётом unsynch

QString get_iso8859_str(function<bool(char *)> getChar, bool unsynch
                        , function<void(void)> fuck_go_back, const long long &duration);

//не чекает BOM
QString get_utf16_str(function<bool(char *)> getChar, bool unsynch, Byte_order bo
                      , function<void(void)> fuck_go_back, const long long &duration);

QString get_utf8_str(function<bool(char *)> getChar, bool unsynch
                     , function<void(void)> fuck_go_back, const long long &duration);

//не чекает BOM
QString get_ucs2_str(function<bool(char *)> getChar, bool unsynch, Byte_order bo
                     , function<void(void)> fuck_go_back, const long long &duration);

//не чекает BOM
QString get_encoding_dependent_string(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                                      , const long long &duration, String_encoding enc, function<bool()> skip);

template<typename T>//
QByteArray get_raw_bytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount);

template<typename T>//
QByteArray get_bytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount);

//РЕАЛИЗАЦИЯ

template<typename T>//getting char & incrementing count
char ch(function<bool(char *)> getChar, T &count)
{
    char c;
    getChar(&c);
    ++count;
    return c;
}

template<typename T>//getting uchar & incrementing count
uchar get(function<bool(char *)> getChar, T &count)
{
    return to_uchar(ch(getChar,count));
}

template<typename T>//getting char w/ unsynch & incrementing count
char uch(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count)
{
    char first = ch(getChar,count);
    if (unsynch && is_255(first))
    {
        if (ch(getChar,count) != 0)
        {
            fuck_go_back();
            --count;
        }
    }
    return first;
}

template<typename T>//getting uchar w/ unsynch & incrementing count
uchar getb(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count)
{
    return to_uchar(uch(getChar,unsynch,fuck_go_back,count));
}

template<typename T>//getting utf8-encoded unicode symbol & incrementing count
ulong get_utf8(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count)
{
    ulong result = 0;
    const mByte first = getb(getChar,unsynch,fuck_go_back,count);
    if (first[7])
    {
        const mByte second = getb(getChar,unsynch,fuck_go_back,count);
        if (first[5])
        {
            const mByte third = getb(getChar,unsynch,fuck_go_back,count);
            if (first[4])
            {
                const mByte fourth = getb(getChar,unsynch,fuck_go_back,count);
                result = first.to_ulong()*64*64*64 + second.to_ulong()*64*64 + third.to_ulong()*64 + fourth.to_ulong();
            }
            else
            {
                result = first.to_ulong()*64*64 + second.to_ulong()*64 + third.to_ulong();
            }
        }
        else
        {
            result = first.to_ulong()*64 + second.to_ulong();
        }
    }
    else
    {
        result = first.to_ulong();
    }
    return result;
}

template<typename T>//getting utf16-encoded unicode symbol & incrementing count
ulong get_utf16(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back, T &count)
{
    uchar msb, lsb;
    if (big_endian)
    {
        msb = getb(getChar,unsynch,fuck_go_back,count);
        lsb = getb(getChar,unsynch,fuck_go_back,count);
    }
    else
    {
        lsb = getb(getChar,unsynch,fuck_go_back,count);
        msb = getb(getChar,unsynch,fuck_go_back,count);
    }
    ulong value1 = static_cast<ulong>(msb)*256 + lsb;

    if (value1 >= 55296 && value1 <= 57343)
    {
        if (big_endian)
        {
            msb = getb(getChar,unsynch,fuck_go_back,count);
            lsb = getb(getChar,unsynch,fuck_go_back,count);
        }
        else
        {
            lsb = getb(getChar,unsynch,fuck_go_back,count);
            msb = getb(getChar,unsynch,fuck_go_back,count);
        }
        ulong value2 = static_cast<ulong>(msb)*256 + lsb;
        value1 -= 55296;//старшие 10 бит
        value2 -= 56320;//младшие 10 бит
        return value1*static_cast<ulong>(power(2,10)) + value2 + static_cast<ulong>(power(2,16));
    }
    else
    {
        return value1;
    }
}

template<typename T>//getting ucs2-encoded unicode symbol & incrementing count
ushort get_ucs2(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back, T &count)
{
    uchar msb, lsb;
    if (big_endian)
    {
        msb = getb(getChar,unsynch,fuck_go_back,count);
        lsb = getb(getChar,unsynch,fuck_go_back,count);
    }
    else
    {
        lsb = getb(getChar,unsynch,fuck_go_back,count);
        msb = getb(getChar,unsynch,fuck_go_back,count);
    }
    return static_cast<ushort>(msb)*256 + lsb;
}

template<typename T>//getting BOM & incrementing count
Byte_order get_BOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count)
{
    uchar first = getb(getChar,unsynch,fuck_go_back,count), second = getb(getChar,unsynch,fuck_go_back,count);
    if (first == 254 && second == 255)
        return big_endian;
    else
    {
        if (first == 255 && second == 254)
            return little_endian;
        else
            return none;
    }
}

/* Нижеследующие функции можно было написать при помощи передачи фиктивного аргумента в уже существующие
 * и не дублировать код, но это бы привело к ненужным действиям в низкоуровневых функциях,
 * которые часто вызываются, и замедлило бы программу. Поэтому пришлось продублировать код.
 */

//getting char
char ch(function<bool(char *)> getChar)
{
    char c;
    getChar(&c);
    return c;
}

//getting uchar
uchar get(function<bool(char *)> getChar)
{
    return to_uchar(ch(getChar));
}

//getting char w/ unsynch
char uch(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    char first = ch(getChar);
    if (unsynch && is_255(first))
    {
        if (ch(getChar) != 0)
            fuck_go_back();
    }
    return first;
}

//getting uchar w/ unsynch
uchar getb(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    return to_uchar(uch(getChar,unsynch,fuck_go_back));
}

//getting utf8-encoded unicode symbol
ulong get_utf8(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    ulong result = 0;
    const mByte first = getb(getChar,unsynch,fuck_go_back);
    if (first[7])
    {
        const mByte second = getb(getChar,unsynch,fuck_go_back);
        if (first[5])
        {
            const mByte third = getb(getChar,unsynch,fuck_go_back);
            if (first[4])
            {
                const mByte fourth = getb(getChar,unsynch,fuck_go_back);
                result = first.to_ulong()*64*64*64 + second.to_ulong()*64*64 + third.to_ulong()*64 + fourth.to_ulong();
            }
            else
            {
                result = first.to_ulong()*64*64 + second.to_ulong()*64 + third.to_ulong();
            }
        }
        else
        {
            result = first.to_ulong()*64 + second.to_ulong();
        }
    }
    else
    {
        result = first.to_ulong();
    }
    return result;
}

//getting utf16-encoded unicode symbol
ulong get_utf16(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back)
{
    uchar msb, lsb;
    if (big_endian)
    {
        msb = getb(getChar,unsynch,fuck_go_back);
        lsb = getb(getChar,unsynch,fuck_go_back);
    }
    else
    {
        lsb = getb(getChar,unsynch,fuck_go_back);
        msb = getb(getChar,unsynch,fuck_go_back);
    }
    ulong value1 = static_cast<ulong>(msb)*256 + lsb;

    if (value1 >= 55296 && value1 <= 57343)
    {
        if (big_endian)
        {
            msb = getb(getChar,unsynch,fuck_go_back);
            lsb = getb(getChar,unsynch,fuck_go_back);
        }
        else
        {
            lsb = getb(getChar,unsynch,fuck_go_back);
            msb = getb(getChar,unsynch,fuck_go_back);
        }
        ulong value2 = static_cast<ulong>(msb)*256 + lsb;
        value1 -= 55296;//старшие 10 бит
        value2 -= 56320;//младшие 10 бит
        return value1*static_cast<ulong>(power(2,10)) + value2 + static_cast<ulong>(power(2,16));
    }
    else
    {
        return value1;
    }
}

//getting ucs2-encoded unicode symbol
ushort get_ucs2(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back)
{
    uchar msb, lsb;
    if (big_endian)
    {
        msb = getb(getChar,unsynch,fuck_go_back);
        lsb = getb(getChar,unsynch,fuck_go_back);
    }
    else
    {
        lsb = getb(getChar,unsynch,fuck_go_back);
        msb = getb(getChar,unsynch,fuck_go_back);
    }
    return static_cast<ushort>(msb)*256 + lsb;
}

//getting BOM
Byte_order get_BOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    uchar first = getb(getChar,unsynch,fuck_go_back), second = getb(getChar,unsynch,fuck_go_back);
    if (first == 254 && second == 255)
        return big_endian;
    else
    {
        if (first == 255 && second == 254)
            return little_endian;
        else
            return none;
    }
}

//СТРОКИ

QString get_iso8859_str(function<bool(char *)> getChar, bool unsynch
                        , function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    char c = 1;
    long long count = 0;
    while (c != 0 && count < duration)
    {
        c = uch(getChar,unsynch,fuck_go_back,count);
        s.append(QChar(c));
    }
    return s;
}

//не чекает BOM
QString get_utf16_str(function<bool(char *)> getChar, bool unsynch, Byte_order bo
                      , function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    bool Big_endian;
    switch (bo)
    {
    case (big_endian):
    {
        Big_endian = true;
        break;
    }
    case(little_endian):
    {
        Big_endian = false;
        break;
    }
    case(none):
        return s;
    }
    ushort c = 1;
    long long count = 0;
    while (c != 0 && count < duration)
    {
        c = cut_ulong(get_utf16(getChar,unsynch,Big_endian,fuck_go_back,count));
        s.append(QChar(c));
    }
    return s;
}

QString get_utf8_str(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    ushort c = 1;
    long long count = 0;
    while (c != 0 && count < duration)
    {
        c = cut_ulong(get_utf8(getChar,unsynch,fuck_go_back,count));
        s.append(QChar(c));
    }
    return s;
}

//не чекает BOM
QString get_ucs2_str(function<bool(char *)> getChar, bool unsynch, Byte_order bo
                     , function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    bool Big_endian;
    switch (bo)
    {
    case(big_endian):
    {
        Big_endian = true;
        break;
    }
    case(little_endian):
    {
        Big_endian = false;
        break;
    }
    case(none):
        return s;
    }
    ushort c = 1;
    long long count = 0;
    while (c != 0 && count < duration)
    {
        c = get_ucs2(getChar,unsynch,Big_endian,fuck_go_back,count);
        s.append(QChar(c));
    }
    return s;
}

template<typename T>
QByteArray get_raw_bytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount)
{
    QByteArray array;
    T count = 0;
    while (count < amount)
        array.append(uch(getChar,unsynch,fuck_go_back,count));
    return array;
}

template<typename T>
QByteArray get_bytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount)
{
    QByteArray array;
    T count = 0;
    while (count < amount)
    {
        array.append(uch(getChar,unsynch,fuck_go_back));
        ++count;
    }
    return array;
}

//не чекает BOM
QString get_encoding_dependent_string(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                                      , const long long &duration, String_encoding enc, function<bool()> skip)
{
    switch (enc)
    {
    case iso_8859_1:
        return get_iso8859_str(getChar,unsynch,fuck_go_back,duration);
    case ucs_2be:
        return get_ucs2_str(getChar,unsynch,big_endian,fuck_go_back,duration);
    case ucs_2le:
        return get_ucs2_str(getChar,unsynch,little_endian,fuck_go_back,duration);
    case utf_16be:
        return get_utf16_str(getChar,unsynch,big_endian,fuck_go_back,duration);
    case utf_16le:
        return get_utf16_str(getChar,unsynch,little_endian,fuck_go_back,duration);
    case utf_8:
        return get_utf8_str(getChar,unsynch,fuck_go_back,duration);
    case not_given:
        skip();
        return QString();
    }
}
