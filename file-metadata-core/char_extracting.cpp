#include "char_extracting.h"
using namespace std;

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
    return toUchar(ch(getChar));
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
    return toUchar(uch(getChar,unsynch,fuck_go_back));
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
ByteOrder get_BOM(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    uchar first = getb(getChar,unsynch,fuck_go_back), second = getb(getChar,unsynch,fuck_go_back);
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

//СТРОКИ

QString getIso8859Str(function<bool(char *)> getChar, bool unsynch
                        , function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    char c = 1;
    ulong count = 0;
    do
    {
        c = uch(getChar,unsynch,fuck_go_back,count);
        if (c)
            s.append(QChar(c));
    } while (c != 0 && count < duration);
    return s;
}

//не чекает BOM
QString getUtf16Str(function<bool(char *)> getChar, bool unsynch, ByteOrder bo
                      , function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    bool Big_endian;
    switch (bo)
    {
    case (bigEndian):
    {
        Big_endian = true;
        break;
    }
    case(littleEndian):
    {
        Big_endian = false;
        break;
    }
    case(none):
        return s;
    }
    ushort c = 1;
    ulong count = 0;
    do
    {
        c = cutUlong(getUtf16(getChar,unsynch,Big_endian,fuck_go_back,count));
        if (c)
            s.append(QChar(c));
    } while (c != 0 && count < duration);
    return s;
}

QString getUtf8Str(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    ushort c = 1;
    ulong count = 0;
    do
    {
        c = cutUlong(getUtf8(getChar,unsynch,fuck_go_back,count));
        if (c)
            s.append(QChar(c));
    } while (c != 0 && count < duration);
    return s;
}

//не чекает BOM
QString getUcs2Str(function<bool(char *)> getChar, bool unsynch, ByteOrder bo
                     , function<void(void)> fuck_go_back, const long long &duration)
{
    QString s;
    bool Big_endian;
    switch (bo)
    {
    case(bigEndian):
    {
        Big_endian = true;
        break;
    }
    case(littleEndian):
    {
        Big_endian = false;
        break;
    }
    case(none):
        return s;
    }
    ushort c = 1;
    ulong count = 0;
    do
    {
        c = getUcs2(getChar,unsynch,Big_endian,fuck_go_back,count);
        if (c)
            s.append(QChar(c));
    } while (c != 0 && count < duration);
    return s;
}

//не чекает BOM
QString getEncodingDependentString(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                                      , const long long &duration, StringEncoding enc)
{
    switch (enc)
    {
    case iso_8859_1:
        return getIso8859Str(getChar,unsynch,fuck_go_back,duration);
    case ucs_2be:
        return getUcs2Str(getChar,unsynch,bigEndian,fuck_go_back,duration);
    case ucs_2le:
        return getUcs2Str(getChar,unsynch,littleEndian,fuck_go_back,duration);
    case utf_16be:
        return getUtf16Str(getChar,unsynch,bigEndian,fuck_go_back,duration);
    case utf_16le:
        return getUtf16Str(getChar,unsynch,littleEndian,fuck_go_back,duration);
    case utf_8:
        return getUtf8Str(getChar,unsynch,fuck_go_back,duration);
    case notGiven:
        return QString();
    }
}

pair<uint, uint> getNumericPair(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                                  , const long long &duration, char separator)
{
    QString first{}, second{};
    char c;
    ulong count{0};

    do
    {
        c = uch(getChar,unsynch,fuck_go_back,count);
        if (c && c !=separator && isDigit(c))
            first += QChar(c);
    } while (c && c != separator && count < duration);

    if (count < duration && c == separator)
    {
        do
        {
            c = uch(getChar,unsynch,fuck_go_back,count);
            if (c && isDigit(c))
                second += QChar(c);
        } while (c && count < duration);
    }

    return make_pair(toUint(first),toUint(second));
}

QList<QString> getList(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back
                       , const long long &duration, int separator, StringEncoding enc)
{
    ulong count{0};
    function<ushort()> ch;

    switch (enc)
    {
    case iso_8859_1: ch = [getChar,unsynch,fuck_go_back,&count]()
                            {
                                return static_cast<ushort>(uch(getChar,unsynch,fuck_go_back,count));
                            }; break;

    case ucs_2be: ch = [getChar,unsynch,fuck_go_back,&count]()
        {
            return getUcs2(getChar,unsynch,true,fuck_go_back,count);
        }; break;

    case ucs_2le: ch = [getChar,unsynch,fuck_go_back,&count]()
        {
            return getUcs2(getChar,unsynch,false,fuck_go_back,count);
        }; break;

    case utf_16be: ch = [getChar,unsynch,fuck_go_back,&count]()
        {
            return cutUlong(getUtf16(getChar,unsynch,true,fuck_go_back,count));
        }; break;

    case utf_16le: ch = [getChar,unsynch,fuck_go_back,&count]()
        {
            return cutUlong(getUtf16(getChar,unsynch,false,fuck_go_back,count));
        }; break;

    case utf_8: ch = [getChar,unsynch,fuck_go_back,&count]()
        {
            return cutUlong(getUtf8(getChar,unsynch,fuck_go_back,count));
        }; break;

    case notGiven: return QList<QString>();
    }

    QList<QString> list{};
    QString s{};
    ushort c{0};

    do
    {
        s.clear();
        do
        {
            c = ch();
            if (c && c != separator)
                s += QChar(c);
        } while (c && c != separator && count < duration);
        list.append(s);
    } while (count < duration);

    return list;
}

StringEncoding getStrEncTwo(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    uchar mark = getb(getChar,unsynch,fuck_go_back);
    switch (mark)
    {
    case 0:
        return iso_8859_1;

    case 1:
        return ucs_2be;

    default:
        return notGiven;
    }
}

StringEncoding getStrEncThree(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    uchar mark = getb(getChar,unsynch,fuck_go_back);
    switch (mark)
    {
    case 0:
        return iso_8859_1;

    case 1:
    {
        ByteOrder bo = get_BOM(getChar,unsynch,fuck_go_back);
        switch (bo)
        {
        case bigEndian:
            return ucs_2be;
        case littleEndian:
            return ucs_2le;
        case none:
            return notGiven;
        }
    }

    default:
        return notGiven;
    }
}

StringEncoding getStrEncFour(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back)
{
    uchar mark = getb(getChar,unsynch,fuck_go_back);
    switch (mark)
    {
    case 0:
        return iso_8859_1;

    case 1:
    {
        ByteOrder bo = get_BOM(getChar,unsynch,fuck_go_back);
        switch (bo)
        {
        case bigEndian:
            return utf_16be;

        case littleEndian:
            return utf_16le;

        case none:
            return notGiven;
        }
    }

    case 2:
        return utf_16be;

    case 3:
        return utf_8;

    default:
        return notGiven;
    }
}

StringEncoding getStringEncoding(function<bool(char *)> getChar, bool unsynch, function<void(void)> fuck_go_back, TagVersion v)
{
    switch (v)
    {
    case noTag:
        return notGiven;

    case two:
        return getStrEncTwo(getChar,unsynch,fuck_go_back);

    case three:
        return getStrEncThree(getChar,unsynch,fuck_go_back);

    case four:
        return getStrEncFour(getChar,unsynch,fuck_go_back);
    }
}
