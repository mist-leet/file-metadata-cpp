#include "char_conversions.h"

uchar toUchar(const QBitArray &a) {
    unsigned char c = 0;
    for (int i = 0;i < 8 && i < a.size();++i)
        if (a.testBit(i))
            c += pow2(i);
    return c;
}

uchar toUchar(char c) {
    QBitArray array(8);
    array = QBitArray::fromBits(&c,8);
    return toUchar(array);
}

uchar toUchar(char source, QBitArray &buffer_array) {
    buffer_array = QBitArray::fromBits(&source,8);
    return toUchar(buffer_array);
}

bool toUchar(const char *sourse, uchar *destination, uint len) {
    if (sourse && destination) {
        QBitArray buffer(8);
        for (uint i = 0;i < len;++i)
            destination[i] = toUchar(sourse[i],buffer);
        return true;
    }
    else
        return false;
}

char toChar(uchar u) {
    QBitArray arr(8);
    return toChar(u,arr);
}

char toChar(uchar u, QBitArray &buffer_array) {
    for (int i = 0;i < 8;++i) {
        buffer_array[i] = u % 2;
        u /= 2;
    }
    return *(buffer_array.bits());
}

bool toChar(const uchar *sourse, char *destination, uint len) {
    if (sourse && destination) {
        QBitArray arr(8);
        for (uint i = 0;i < len;++i)
            destination[i] = toChar(sourse[i],arr);
        return true;
    }
    else
        return false;
}

bool valueToBits(char *destination, ulong value) {
    if (destination) {
        QBitArray buffer_array(8);
        for (int i = 3;i >= 0;--i) {
            destination[i] = toChar(value % 256,buffer_array);
            value /= 256;
        }
        return true;
    }
    else
        return false;
}

bool valueToBits(uchar *destination, ulong value) {
    if (destination) {
        for (int i = 3;i >= 0;--i) {
            destination[i] = value % 256;
            value /= 256;
        }
        return true;
    }
    else
        return false;
}

bool is_255(char c) {
    QBitArray buffer(8);
    buffer = QBitArray::fromBits(&c,8);
    return buffer.count(false) == 0;
}

bool is_255(uchar c) {
    return c == 255;
}

uchar toUchar(uchar u) {
    return u;
}

bool notNull(QChar c) {
    return c.unicode();
}

ushort cutUlong(ulong code) {
    if (code > USHRT_MAX)//2^16 - 1
        return 65533;//возвращает заменяющий символ если переданный символ нельзя представить 16 битами
    else
        return static_cast<ushort>(code);
}

ulong pow2(int p) {
    if (p < 0)
        return 0;
    else {
        ulong val{1};
        for (int i = 0;i < p;++i)
            val *= 2;
        return val;
    }
}
