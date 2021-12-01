#include "v24.h"
#include "v1.h"
using namespace std;

Binary::operator bool() const
{
    return finely_opened;
}

Binary::~Binary()
{
    close();
}

Binary & Binary::operator << (const string & s)
{
    write(s.c_str(),s.size());
    return *this;
}

Binary & Binary::operator << (char c)
{
    write(&c,1);
    return *this;
}

Binary & Binary::operator >> (char & c)
{
    getChar(&c);
    return *this;
}

unsigned char Binary::get()
{
    char c;
    getChar(&c);
    return to_u_char(c);
}

unsigned char Binary::getb(bool unsynch)
{
    unsigned char first = get();
    if (unsynch)
        if (get() != 0 || first != 255)
            seek(pos() - 1);
    return first;
}

long Binary::get_utf8(bool unsynch)
{
    unsigned long result = 0;
    const bitset<8> first = getb(unsynch);
    if (first.test(7))
    {
        const Byte second = getb(unsynch);
        if (first.test(5))
        {
            const Byte third = getb(unsynch);
            if (first.test(4))
            {
                const Byte fourth = getb(unsynch);
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
    return static_cast<long>(result);
}

long Binary::get_utf16(bool unsynch, bool big_endian)
{
    unsigned char msb, lsb;
    if (big_endian)
    {
        msb = getb(unsynch);
        lsb = getb(unsynch);
    }
    else
    {
        lsb = getb(unsynch);
        msb = getb(unsynch);
    }
    long value1 = static_cast<long>(msb)*256 + static_cast<long>(lsb);

    if (value1 >= 55296 && value1 <= 57343)
    {
        if (big_endian)
        {
            msb = getb(unsynch);
            lsb = getb(unsynch);
        }
        else
        {
            lsb = getb(unsynch);
            msb = getb(unsynch);
        }
        long value2 = static_cast<long>(msb)*256 + static_cast<long>(lsb);
        value1 -= 55296;//старшие 10 бит
        value2 -= 56320;//младшие 10 бит
        long result = value1*static_cast<long>(power(2,10)) + value2;
        return result + static_cast<long>(power(2,16));
    }
    else
    {
        return value1;
    }
}

long Binary::get_usc2(bool unsynch, bool big_endian)
{
    unsigned char msb, lsb;
    if (big_endian)
    {
        msb = getb(unsynch);
        lsb = getb(unsynch);
    }
    else
    {
        lsb = getb(unsynch);
        msb = getb(unsynch);
    }
    return static_cast<long>(msb)*256 + lsb;
}

Binary::byte_order Binary::get_BOM(bool unsynch)
{
    unsigned char first = getb(unsynch), second = getb(unsynch);
    if (first == 254 && second == 255)
        return big_endian;
    else
    {
        if (first == 255 && second == 254)
            return little_endian;
        else
            return wrong;
    }
}

char Binary::ch()
{
    char c;
    getChar(&c);
    return c;
}

char Binary::_ch(bool unsynch)
{
    char first = ch(), second = ch();
    QBitArray sec(8);
    sec = QBitArray::fromBits(&second, 8);
    if (unsynch)
        if (first != 0 || sec.count(true) != 8)
            seek(pos() - 1);
    return first;
}
