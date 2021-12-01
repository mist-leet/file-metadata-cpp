#include "char_conversions.h"
using namespace std;

uchar to_uchar(const QBitArray & a)
{
    unsigned char c = 0;
    for (int i = 0;i < 8 && i < a.size();++i)
        if (a.testBit(i))
            c += power(2,i);
    return c;
}

uchar to_uchar(char c)
{
    QBitArray array(8);
    array = QBitArray::fromBits(&c,8);
    return to_uchar(array);
}

uchar to_uchar(char source, QBitArray & buffer_array)
{
    buffer_array = QBitArray::fromBits(&source,8);
    return to_uchar(buffer_array);
}

bool to_uchar(const char * const sourse, uchar * const destination, uint len)
{
    if (sourse && destination)
    {
        QBitArray buffer(8);
        for (uint i = 0;i < len;++i)
            destination[i] = to_uchar(sourse[i],buffer);
        return true;
    }
    else
        return false;
}

char to_char(uchar u)
{
    QBitArray arr(8);
    return to_char(u,arr);
}

char to_char(uchar u, QBitArray & buffer_array)
{
    for (int i = 0;i < 8;++i)
    {
        buffer_array[i] = u % 2;
        u /= 2;
    }
    return *(buffer_array.bits());
}

bool to_char(const uchar * const sourse, char * const destination, uint len)
{
    if (sourse && destination)
    {
        QBitArray arr(8);
        for (uint i = 0;i < len;++i)
            destination[i] = to_char(sourse[i],arr);
        return true;
    }
    else
        return false;
}

bool value_to_bits(char * const destination, ulong value)
{
    if (destination)
    {
        QBitArray buffer_array(8);
        for (int i = 3;i >= 0;--i)
        {
            destination[i] = to_char(value % 256,buffer_array);
            value /= 256;
        }
        return true;
    }
    else
        return false;
}

bool value_to_bits(uchar * const destination, ulong value)
{
    if (destination)
    {
        for (int i = 3;i >= 0;--i)
        {
            destination[i] = value % 256;
            value /= 256;
        }
        return true;
    }
    else
        return false;
}

bool is_255(char c)
{
    QBitArray buffer(8);
    buffer = QBitArray::fromBits(&c,8);
    return buffer.count(false) == 0;
}
