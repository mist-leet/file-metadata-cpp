#include "new_char_extracting.h"
using std::function;

char extr::ch(std::function<bool (char *)> getChar) {
    char c;
    getChar(&c);
    return c;
}

uchar extr::get(std::function<bool (char *)> getChar) {
    char c;
    getChar(&c);
    return toUchar(c);
}

QChar extr::getUtf8(std::function<uchar ()> gc) {
    qDebug() << "Call to getUtf8";
    ulong result = 0;
    mByte first = gc();
    if (first[7]) {
        mByte second = gc();
        if (first[5]) {
            mByte third = gc();
            if (first[4]) {
                mByte fourth = gc();
                first[7] = first[6] = first[5] = first[4] = 0;
                second[7] = third[7] = fourth[7] = 0;
                result = first.to_ulong()*64*64*64 + second.to_ulong()*64*64 + third.to_ulong()*64 + fourth.to_ulong();
            }
            else {
                first[7] = first[6] = first[5] = 0;
                second[7] = third[7] = 0;
                result = first.to_ulong()*64*64 + second.to_ulong()*64 + third.to_ulong();
            }
        }
        else {
            first[7] = first[6] = 0;
            second[7] = 0;
            result = first.to_ulong()*64 + second.to_ulong();
        }
    }
    else {
        result = first.to_ulong();
    }
    qDebug() << "getUtf8 got" << cutUlong(result) << endl;
    return QChar(cutUlong(result));
}

QChar extr::getUtf16(std::function<uchar ()> gc, bool bigEndian) {
    uchar msb, lsb;
    if (bigEndian) {
        msb = gc();
        lsb = gc();
    }
    else {
        lsb = gc();
        msb = gc();
    }
    ulong value1 = static_cast<ulong>(msb)*256 + lsb;

    if (value1 >= 55296 && value1 <= 57343) {
        if (bigEndian) {
            msb = gc();
            lsb = gc();
        }
        else {
            lsb = gc();
            msb = gc();
        }
        ulong value2 = static_cast<ulong>(msb)*256 + lsb;
        value1 -= 55296;//старшие 10 бит
        value2 -= 56320;//младшие 10 бит
        return QChar(cutUlong(value1*static_cast<ulong>(pow2(10)) + value2 + static_cast<ulong>(pow2(16))));
    }
    else
        return QChar(cutUlong(value1));
}

QChar extr::getUcs2(std::function<uchar ()> gc, bool bigEndian) {
    uchar msb, lsb;
    if (bigEndian) {
        msb = gc();
        lsb = gc();
    }
    else {
        lsb = gc();
        msb = gc();
    }
    return QChar(static_cast<ushort>(msb)*256 + lsb);
}

ByteOrder extr::getBOM(std::function<uchar ()> gc) {
    qDebug() << "extr::getBOM: calling main getBOM function\n";
    uchar first = gc();
    uchar second = gc();
    if (first == 254 && second == 255) {
        qDebug() << "extr::getBOM: got big endian\n";
        return bigEndian;
    }
    else {
        if (first == 255 && second == 254) {
            qDebug() << "extr::getBOM: got little endian\n";
            return littleEndian;
        }
        else {
            qDebug() << "extr::getBOM: no BOM\n";
            return none;
        }
    }
}

std::vector<uchar> extr::vGetBytes(std::function<uchar()> gc, bool unsynch, std::function<void(void)> back, ulong len) {//unsynch
    if (unsynch) {
        std::vector<uchar> v{};
        ulong count = 0;
        while (count < len)
            v.push_back(extr::getUns(gc, unsynch, back, count));
        return v;
    }
    else
        return extr::vGetBytes(gc, len);
}

std::vector<uchar> extr::vGetBytes(std::function<uchar()> gc, ulong len) {//no unsynch
    std::vector<uchar> v{};
    ulong count = 0;
    while (count < len) {
        ++count;
        v.push_back(gc());
    }
    return v;
}

QString extr::getqString(std::function<QChar(ulong &)> getqc, ulong len) {
    qDebug() << "extr, getqString: start\n";
    QString s{};
    QChar c{};
    ulong count{0};
    do {
        c = getqc(count);
        if (notNull(c))
            s.append(c);
    } while (notNull(c) && count < len);
    qDebug() << "extr, getqString: got '" << s << "'\n";
    return s;
}

QList<QString> extr::getList(std::function<QChar(ulong &)> getqc, ulong len, QChar separator) {
    ulong count{0};
    QList<QString> l{};
    QString s{};
    QChar c{};

    do {
        s.clear();
        do
        {
            c = getqc(count);
            if (notNull(c) && c != separator)
                s.append(c);
        } while (notNull(c) && c != separator && count < len);
        l.append(s);
    } while (count < len);
    return l;
}

ulong extr::get32Bit(std::function<uchar()> gt) {
    ulong num = 0;
    for (int i = 3;i >=0;--i)
        num += static_cast<ulong>(gt())*Gl::power(256,i);
    return num;
}

char extr::ch(std::function<bool (char *)> getChar, ulong &count) {
    char c;
    getChar(&c);
    ++count;
    return c;
}

uchar extr::get(std::function<bool (char *)> getChar, ulong &count) {
    char c;
    getChar(&c);
    ++count;
    return toUchar(c);
}

QChar extr::getUtf8(std::function<uchar ()> gc, ulong &count) { //no unsynch
    return extr::getUtf8([&count,gc]() {
        ++count;
        return gc();
    });
}

QChar extr::getUtf8(std::function<uchar ()> gc, bool unsynch, std::function<void ()> back, ulong &count) { //unsynch
    return extr::getUtf8([gc, unsynch, back, &count]()->uchar {
        return extr::getUns(gc, unsynch, back, count);
    });
}

QChar extr::getUtf16(std::function<uchar ()> gc, ulong &count, bool bigEndian) { //no unsynch
    return extr::getUtf16([gc, &count]() {
        ++count;
        return gc();
    }, bigEndian);
}

QChar extr::getUtf16(std::function<uchar ()> gc, bool unsynch, std::function<void ()> back, ulong &count, bool bigEndian) { //unsynch
    return extr::getUtf16([gc, unsynch, back, &count]()->uchar {
        return extr::getUns(gc, unsynch, back, count);
    }, bigEndian);
}

QChar extr::getUcs2(std::function<uchar ()> gc, ulong &count, bool bigEndian) { //no unsynch
    return extr::getUcs2([gc, &count]() {
        ++count;
        return gc();
    }, bigEndian);
}

QChar extr::getUcs2(std::function<uchar ()> gc, bool unsynch, std::function<void ()> back, ulong &count, bool bigEndian)//unsynch
{
    return extr::getUcs2([gc, unsynch, back, &count]()->uchar
    {
        return extr::getUns(gc, unsynch, back, count);
    }, bigEndian);
}

ByteOrder extr::getBOM(std::function<uchar ()> gc, ulong &count) {
    qDebug() << "extr, getBOM: calling without unsynch\n";
    return extr::getBOM([gc, &count]() {
        ++count;
        return gc();
    });
}

ByteOrder extr::getBOM(std::function<uchar ()> gc, bool unsynch, std::function<void ()> back, ulong &count) {
    return extr::getBOM([gc, unsynch, back, &count]()->uchar {
        return extr::getUns(gc, unsynch, back, count);
    });
}
