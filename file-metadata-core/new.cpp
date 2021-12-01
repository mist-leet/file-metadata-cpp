#include "new.h"
using namespace std;

Restrictions::operator bool()
{
    return precense;
}

Raw_data::operator bool()
{
    return compression;
}

ostream & operator << (ostream & stream, const QBitArray & array)
{
    stream << noboolalpha;
    for (int i = array.size() - 1;i >=0;--i)
        stream << array.testBit(i);
    return stream;
}

long long power(int num, int pow)
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

unsigned char to_u_char(QBitArray a)
{
    unsigned char c = 0;
    for (int i = 0;i < 8 && i < a.size();++i)
        if (a.testBit(i))
            c += power(2,i);
    return c;
}

unsigned char to_u_char(char c)
{
    QBitArray array(8);
    array = QBitArray::fromBits(&c,8);
    return to_u_char(array);
}
