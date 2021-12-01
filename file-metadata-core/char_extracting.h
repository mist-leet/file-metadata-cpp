#pragma once
#include "char_conversions.h"
using namespace std;
/*
 * bool getChar(char *);//достаёт char из файла/структуры и кладёт по указанному адресу
 */

//------------------------------------чтение символов с инкрементацией счётчика-----------------------------------------

template<typename T>//getting char & incrementing count
char ch(function<bool(char *)> getChar, T &count);

template<typename T>//getting uchar & incrementing count
uchar get(function<bool(char *)> getChar, T &count);

template<typename T>//getting char w/ unsynch & incrementing count
char uch(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting uchar w/ unsynch & incrementing count
uchar getb(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting utf8-encoded unicode symbol & incrementing count
ulong getUtf8(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting utf16-encoded unicode symbol & incrementing count
ulong getUtf16(function<bool(char *)> getChar, bool unsynch, bool bigEndian, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting ucs2-encoded unicode symbol & incrementing count
ushort getUcs2(function<bool(char *)> getChar, bool unsynch, bool bigEndian, function<void(void)> fuck_go_back, T &count);

template<typename T>//getting BOM & incrementing count
ByteOrder getBOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count);

//----------------------------------чтение символов без инкрементации счётчика--------------------------------------------

//getting char
char ch(function<bool(char *)> getChar);

//getting uchar
uchar get(function<bool(char *)> getChar);

//getting char w/ unsynch
char uch(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//getting uchar w/ unsynch
uchar getb(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//getting utf8-encoded unicode symbol
ulong getUtf8(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//getting utf16-encoded unicode symbol
ulong getUtf16(function<bool(char *)> getChar, bool unsynch, bool bigEndian, function<void(void)> fuck_go_back);

//getting ucs2-encoded unicode symbol
ushort getUcs2(function<bool(char *)> getChar, bool unsynch, bool bigEndian, function<void(void)> fuck_go_back);

//getting BOM
ByteOrder getBOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//-----------------------------чтение строк в разных кодировках с учётом unsynch-----------------------------------

QString getIso8859Str(function<bool(char *)> getChar, bool unsynch
                        , function<void(void)> fuck_go_back, const long long &duration);

//не чекает BOM
QString getUtf16Str(function<bool(char *)> getChar, bool unsynch, ByteOrder bo
                      , function<void(void)> fuck_go_back, const long long &duration);

QString getUtf8Str(function<bool(char *)> getChar, bool unsynch
                     , function<void(void)> fuck_go_back, const long long &duration);

//не чекает BOM
QString getUcs2Str(function<bool(char *)> getChar, bool unsynch, ByteOrder bo
                     , function<void(void)> fuck_go_back, const long long &duration);

//не чекает BOM
QString getEncodingDependentString(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                                      , const long long &duration, StringEncoding enc);

//-----------------------------------------------вспомогательные функции----------------------------------------------

template<typename T>//
QByteArray getBytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount);

template<typename T>//
QByteArray getCountBytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount);

//пара чисел, закодированных в iso-8859-1 и разделённых separator'ом
pair<uint, uint> getNumericPair(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                                  , const long long &duration, char separator);

//список полей, разделённых separator'ом
QList<QString> getList(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                       , const long long &duration, int separator, StringEncoding enc);

//доставание кодировки для 2.2
StringEncoding getStrEncTwo(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//доставание кодировки для 2.3
StringEncoding getStrEncThree(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//доставание кодировки для 2.4
StringEncoding getStrEncFour(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back);

//доставание кодировки для 2.v
StringEncoding getStringEncoding(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, TagVersion v);

//---------------------------------------------------------РЕАЛИЗАЦИЯ------------------------------------------------------------

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
    return toUchar(ch(getChar,count));
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
    return toUchar(uch(getChar,unsynch,fuck_go_back,count));
}

template<typename T>//getting utf8-encoded unicode symbol & incrementing count
ulong getUtf8(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count)
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
ulong getUtf16(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back, T &count)
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
ushort getUcs2(function<bool(char *)> getChar, bool unsynch, bool big_endian, function<void(void)> fuck_go_back, T &count)
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
ByteOrder getBOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T &count)
{
    uchar first = getb(getChar,unsynch,fuck_go_back,count), second = getb(getChar,unsynch,fuck_go_back,count);
    if (first == 254 && second == 255)
        return bigEndian;
    else
    {
        if (first == 255 && second == 254)
            return littleEndian;
        else
            return none;
    }
}

template<typename T>
QByteArray getBytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount)
{
    QByteArray array;
    T count = 0;
    while (count < amount)
        array.append(uch(getChar,unsynch,fuck_go_back,count));
    return array;
}

template<typename T>
QByteArray getCountBytes(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, T amount)
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
