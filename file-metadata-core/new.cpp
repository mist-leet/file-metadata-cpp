#include "new.h"
using namespace std;

ostream & operator << (ostream &stream, const QBitArray &array)
{
    stream << noboolalpha;
    for (int i = array.size() - 1;i >=0;--i)
        stream << array.testBit(i);
    return stream;
}

long long power(long long num, int pow)
{
    if (pow < 0)
        return 0;
    else
    {
        long long k = 1;
        for (int i = pow;i > 0;--i)
            k *= num;
        return k;
    }
}

ushort cutUlong(ulong code)
{
    if (code > 65535)//2^16 - 1
        return 65533;//возвращает заменяющий символ если переданный символ нельзя представить 16 битами
    else
        return static_cast<ushort>(code);
}

QByteArray qUncompressWrapper(const QByteArray &raw_data, ulong expected_size)
{
    QByteArray copy(raw_data);
    char expected_size_storage[4];
    valueToBits(expected_size_storage,expected_size);
    copy.prepend(expected_size_storage,4);
    return qUncompress(copy);
}

QByteArray qUncompressWrapper(QByteArray &&raw_data, ulong expected_size)
{
    char expected_size_storage[4];
    valueToBits(expected_size_storage,expected_size);
    raw_data.prepend(expected_size_storage,4);
    return qUncompress(raw_data);
}

uint toUint(const QString &s)
{
    uint a = 0;
    for (int i = s.length() - 1;i >= 0;--i)
        if (s[i].isDigit())
            a += s[i].unicode()*power(10,i);
    return a;
}
