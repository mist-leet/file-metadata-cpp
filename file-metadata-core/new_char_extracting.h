#pragma once
#include "char_conversions.h"
#include "global_functions.h"

namespace extr {
char ch(std::function<bool(char *)>);       //без счётчика
char ch(std::function<bool(char *)>, ulong&);   //с счётчиком

uchar get(std::function<bool(char *)>);     //без счётчика
uchar get(std::function<bool(char *)>, ulong&); //с счётчиком

template <typename T, class = std::enable_if_t<anyChar<T>>>
T getUns(std::function<T()>, bool, std::function<void()>);
template <typename T, class = std::enable_if_t<anyChar<T>>>
T getUns(std::function<T()>, bool, std::function<void(void)>, ulong&);  //с счётчиком

template <typename T, class = std::enable_if_t<anyChar<T>>>
T get(std::function<T()>, ulong&);

ulong get32Bit(std::function<uchar()>);
template <typename T, class = std::enable_if_t<anyChar<T>>>
ulong get32Bit(std::function<T()>, ulong&);
template <typename T, class = std::enable_if_t<anyChar<T>>>
ulong get32Bit(std::function<T()>, bool, std::function<void(void)>, ulong&);

QChar getUtf8(std::function<uchar()>);                                      //логика
QChar getUtf8(std::function<uchar()>, ulong&);                                  //no unsynch
QChar getUtf8(std::function<uchar()>, bool, std::function<void(void)> , ulong&);//unsynch

QChar getUtf16(std::function<uchar()>, bool);                                       //логика
QChar getUtf16(std::function<uchar()>, ulong&, bool);                                   //no unsynch
QChar getUtf16(std::function<uchar()>, bool, std::function<void(void)> , ulong&, bool); //unsynch

QChar getUcs2(std::function<uchar()>, bool);                                        //логика
QChar getUcs2(std::function<uchar()>, ulong&, bool = true);                                    //no unsynch
QChar getUcs2(std::function<uchar()>, bool, std::function<void(void)> , ulong&, bool = true);  //unsynch

ByteOrder getBOM(std::function<uchar()>);                                       //логика
ByteOrder getBOM(std::function<uchar()>, ulong&);                                   //no unsynch
ByteOrder getBOM(std::function<uchar()>, bool, std::function<void(void)> , ulong&); //unsynch

template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunction(std::function<T()>, TagVersion, bool&, ulong&);//no unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunction(std::function<T()>, bool, std::function<void()>, TagVersion, bool&, ulong&);//unsynch

template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunctionV2(std::function<T()>, bool&, ulong&); //V2 no unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunctionV3(std::function<T()>, bool&, ulong&); //V3 no unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunctionV4(std::function<T()>, bool&, ulong&); //V4 no unsynch

template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunctionV2(std::function<T()>, bool, std::function<void()>, bool&, ulong&); //V2 unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunctionV3(std::function<T()>, bool, std::function<void()>, bool&, ulong&); //V3 unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
std::function<QChar(ulong&)> getFunctionV4(std::function<T()>, bool, std::function<void()>, bool&, ulong&); //V4 unsynch

QString getqString(std::function<QChar(ulong&)>, ulong);//                                                      логика
template <typename T, class = std::enable_if_t<anyChar<T>>>
QString getEncodingDependentString(std::function<T()>, bool, std::function<void(void)>, ulong, TagVersion);//   unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
QString getEncodingDependentString(std::function<T()>, ulong, TagVersion);//                                    no unsynch

template <typename T, class = std::enable_if_t<anyChar<T>>>
QString getUrl(std::function<T()>, bool, std::function<void(void)>, ulong);
template <typename T, class = std::enable_if_t<anyChar<T>>>
QString getUrl(std::function<T()>, ulong);

std::vector<uchar> vGetBytes(std::function<uchar()>, bool, std::function<void(void)>, ulong);//      unsynch
std::vector<uchar> vGetBytes(std::function<uchar()>, ulong);//                                       no unsynch

//пара чисел, закодированных в iso-8859-1 и разделённых символом T
template <typename T, class = std::enable_if_t<anyChar<T>>>
std::pair<uint, uint> getNumericPair(std::function<T()>, bool, std::function<void(void)>, ulong, T); //unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
std::pair<uint, uint> getNumericPair(std::function<T()>, ulong, T);                                  //no unsynch

//список полей, разделённых QChar'ом
QList<QString> getList(std::function<QChar(ulong&)>, ulong, QChar);//                                       логика
template <typename T, class = std::enable_if_t<anyChar<T>>>
QList<QString> getList(std::function<T()>, bool, std::function<void(void)>, ulong, TagVersion, QChar);//unsynch
template <typename T, class = std::enable_if_t<anyChar<T>>>
QList<QString> getList(std::function<T()>, ulong, TagVersion, QChar);//                                 no unsynch
} //namespace extr

char extr::ch(std::function<bool(char *)> getChar, ulong &count);

uchar extr::get(std::function<bool(char *)> getChar, ulong &count);

template <typename T, class>
T extr::getUns(std::function<T()> gc, bool unsynch, std::function<void()> back) {
    T first = gc();
    if (unsynch && is_255(first)) {
        if (gc() != 0)
            back();
    }
    return first;
}

template <typename T, class>
T extr::getUns(std::function<T()> gc, bool unsynch, std::function<void(void)> back, ulong &count) {
    T first = gc();
    ++count;
    if (unsynch && is_255(first)) {
        if (gc() == 0)
            ++count;
        else
            back();
    }
    return first;
}

template <typename T, class>
T extr::get(std::function<T()> gc, ulong &count) {
    ++count;
    return gc();
}

QChar extr::getUtf8(std::function<uchar()> gc, ulong &count);

QChar extr::getUtf8(std::function<uchar()> gc, bool unsynch, std::function<void(void)> back, ulong &count);

QChar extr::getUtf16(std::function<uchar()> gc, ulong &count, bool bigEndian);

QChar extr::getUtf16(std::function<uchar()> gc, bool unsynch, std::function<void(void)> back, ulong &count, bool bigEndian);

QChar extr::getUcs2(std::function<uchar()> gc, ulong &count, bool bigEndian);

QChar extr::getUcs2(std::function<uchar()> gc, bool unsynch, std::function<void(void)> back, ulong &count, bool bigEndian);

ByteOrder extr::getBOM(std::function<uchar()> gc, ulong &count);

ByteOrder extr::getBOM(std::function<uchar()> gc, bool unsynch, std::function<void(void)> back, ulong &count);

template <typename T, class>//unsynch
QString extr::getEncodingDependentString(std::function<T()> gc, bool unsynch, std::function<void(void)> back, ulong len, TagVersion v) {
    if (unsynch) {
        qDebug() << "extr, getEncodingDependentString: getting with unsynch, length =" << len << "version is" << v + 2 << endl;
        ulong spentOnCheck = 0;
        bool correctMark = true;
        qDebug() << "extr, getEncodingDependentString: calling getFunction\n";
        std::function<QChar(ulong&)> getqc = extr::getFunction(gc, unsynch, back, v, correctMark, spentOnCheck);
        if (correctMark) {
            qDebug() << "extr: got correct mark, calling getqString, length =" << len - spentOnCheck << endl;
            return extr::getqString(getqc,len - spentOnCheck);
        }
        else {
            qDebug() << "extr, getEncodingDependentString: got incorrect encoding mark\n";
            return QString();
        }
    }
    else {
        qDebug() << "extr, getEncodingDependentString: no unsynch found, redirect to function with no unsynch\n";
        return extr::getEncodingDependentString(gc, len, v);
    }
}

template <typename T, class>//no unsynch
QString extr::getEncodingDependentString(std::function<T()> gc, ulong len, TagVersion v) {
    qDebug() << "extr: called encoding dependent strint with no unsynch, length =" << len << ", version is" << v + 2 << endl;
    ulong spentOnCheck = 0;
    bool correctMark = true;
    std::function<QChar(ulong&)> getqc = extr::getFunction(gc, v, correctMark,spentOnCheck);
    if (correctMark) {
        qDebug() << "extr, getEncodingDependentString: mark is correct, parsing\n";
        return extr::getqString(getqc, len - spentOnCheck);
    }
    else {
        qDebug() << "extr, getEncodingDependentString: mark is incorrect, returning null string\n";
        return QString();
    }
}

template <typename T, class>//список полей, разделённых QChar'ом; no unsynch
QList<QString> extr::getList(std::function<T()> gc, bool unsynch,
                             std::function<void(void)> back, ulong len, TagVersion v, QChar separator) {
    if (unsynch) {
        bool correctMark = true;
        ulong spentOnMark = 0;
        std::function<QChar(ulong&)> getqc = extr::getFunction(gc, unsynch, back, v, correctMark, spentOnMark);
        if (correctMark)
            return extr::getList(getqc, len - spentOnMark, separator);
        else
            return QList<QString>();
    }
    else {
        return extr::getList(gc, len, v, separator);
    }
}

template <typename T, class>//no unsynch
QList<QString> extr::getList(std::function<T()> gc, ulong len, TagVersion v, QChar separator) {
    bool correctMark = true;
    ulong spentOnMark = 0;
    std::function<QChar(ulong&)> getqc = extr::getFunction(gc, v, correctMark, spentOnMark);

    if (correctMark) {
        return extr::getList(getqc, len - spentOnMark, separator);
    }
    else {
        return QList<QString>();
    }
}

//пара чисел, закодированных в iso-8859-1 и разделённых символом T
template <typename T, class>//unsynch
std::pair<uint, uint> extr::getNumericPair(std::function<T()> gc, bool unsynch,
                                           std::function<void(void)> back, ulong len, T separator) {
    if (unsynch) {
        QString first{}, second{};
        QChar c{};
        ulong count{0};

        do {
            c = QChar(extr::getUns(gc, unsynch, back, count));
            if (c.isDigit() && c != QChar(separator))
                first.append(c);
        } while (notNull(c) && c != separator && count < len);

        if (count < len) {
            do {
                c = QChar(extr::getUns(gc, unsynch, back, count));
                if (c.isDigit())
                    second.append(c);
            } while (notNull(c) && count < len);
        }

        return std::make_pair(Gl::toUint(first), Gl::toUint(second));
    }
    else
        return extr::getNumericPair(gc, len, separator);
}

template <typename T, class>//no unsynch
std::pair<uint, uint> extr::getNumericPair(std::function<T()> gc, ulong len, T separator) {
    QString first{}, second{};
    QChar c{};
    ulong count{0};

    do {
        c = QChar(gc());
        ++count;
        if (c.isDigit() && c != QChar(separator))
            first.append(c);
    } while (notNull(c) && c != separator && count < len);

    if (count < len) {
        do {
            c = QChar(gc());
            ++count;
            if (c.isDigit())
                second.append(c);
        } while (notNull(c) && count < len);
    }

    return std::make_pair(Gl::toUint(first), Gl::toUint(second));
}

template <typename T, class>//no unsynch
std::function<QChar(ulong&)> extr::getFunction(std::function<T()> gc, TagVersion v, bool &correct, ulong &spentOnCheck) {
    qDebug() << "getFunction: called without unsynch\n";
    correct = true;
    switch (v) {
    case noTag: {
        correct = false;
        return [](ulong&) {
            return QChar();
        };
    }//case no tag
    case two: return extr::getFunctionV2(gc, correct, spentOnCheck);
    case three: return extr::getFunctionV3(gc, correct, spentOnCheck);
    case four: return extr::getFunctionV4(gc, correct, spentOnCheck);
    }//switch (tag version)
}

template <typename T, class>
std::function<QChar(ulong&)> extr::getFunction
    (std::function<T()> gc, bool unsynch, std::function<void()> back, TagVersion v, bool &correct, ulong &spentOnCheck) {
    if (unsynch) {
        qDebug() << "getFunction: called with unsynch\n";
        correct = true;
        switch (v) {
        case noTag: {
            correct = false;
            return [](ulong&) {
                return QChar();
            };
        }//case no tag
        case two: return extr::getFunctionV2(gc, unsynch, back, correct, spentOnCheck);
        case three: return extr::getFunctionV3(gc, unsynch, back, correct, spentOnCheck);
        case four: return extr::getFunctionV4(gc, unsynch, back, correct, spentOnCheck);
        }//switch (tag version)
    }
    else {
        qDebug() << "getFunction: redirect to getFunction with no unsynch\n";
        return extr::getFunction(gc, v, correct, spentOnCheck);
    }
}

template<typename T, class >
QString extr::getUrl(std::function<T ()> gc, bool unsynch, std::function<void ()> back, ulong len)
{
    if (unsynch)
    {
        return extr::getqString([gc, unsynch, back](ulong &c)
        {
            return QChar(extr::getUns(gc, unsynch, back, c));
        }, len);
    }
    else
        return extr::getUrl(gc, len);
}

template<typename T, class >
QString extr::getUrl(std::function<T ()> gc, ulong len) {
    return extr::getqString([gc](ulong &c) {
        ++c;
        return QChar(gc());
    }, len);
}

template <typename T, class>
ulong extr::get32Bit(std::function<T()> gt, ulong &count) {
    return extr::get32Bit(
                    [gt, &count]() {
                        ++count;
                        return toUchar(gt());
                    });
}

template <typename T, class>
ulong extr::get32Bit(std::function<T()> gt, bool unsynch, std::function<void(void)> back, ulong &count)
{
    if (unsynch) {
        return extr::get32Bit(
                    [gt, unsynch, back, &count]() {
            return toUchar(getUns(gt, unsynch, back, count));
        });
    }
    else {
        return extr::get32Bit(gt, count);
    }
}

template <typename T, class>//V2 no unsynch
std::function<QChar(ulong&)> extr::getFunctionV2(std::function<T()> gc, bool &correct, ulong &count) {
    T mark = gc();
    ++count;
    std::function<uchar()> _uchar = [gc] {
        return toUchar(gc());
    };

    switch (mark) {
    case 0: return [gc](ulong &c) {
            ++c;
            return QChar(gc());
        };//case 0

    case 1: return [_uchar](ulong &c) {
            return extr::getUcs2(_uchar, c);
        };//case 1

    default: {
        correct = false;
        return [](ulong&){
            return QChar();
        };//default
    }
    }//switch (mark)
}

template <typename T, class>//V3 no unsynch
std::function<QChar(ulong&)> extr::getFunctionV3(std::function<T()> gc, bool &correct, ulong &count) {
    qDebug() << "getFunction, V3: called with no unsynch\n";
    T mark = gc();
    qDebug() << "getFunction, V3, no unsynch: got mark =" << int(mark) << endl;
    ++count;
    std::function<uchar()> _uchar = [gc] {
        return toUchar(gc());
    };

    switch (mark) {
    case 0: return [gc](ulong &c){
            ++c;
            return QChar(gc());
        };//case 0

    case 1: {
        ByteOrder bo = extr::getBOM(_uchar, count);

        switch (bo) {
        case littleEndian: return [_uchar](ulong &c) {
                return extr::getUcs2(_uchar, c, false);
            };//ByteOrder = littleEndian

        case bigEndian: return [_uchar](ulong &c) {
                return extr::getUcs2(_uchar, c, true);
            };//ByteOrder = bigEndian

        case none: {
            correct = false;
            return [](ulong&) {
                return QChar();
            };
        }//ByteOrder = none

        }//switch ByteOrder
    }//case 1

    default: {
        correct = false;
        return [](ulong&) {
            return QChar();
        };
    }//default

    }//switch (mark)
}

template <typename T, class>//V4 no unsynch
std::function<QChar(ulong&)> extr::getFunctionV4(std::function<T()> gc, bool &correct, ulong &count) {
    T mark = gc();
    qDebug() << "getFunctionV4 with no unsynch: mark =" << int(mark) << endl;
    ++count;
    std::function<uchar()> _uchar = [gc] {
        return toUchar(gc());
    };

    switch (mark) {
    case 0: return [gc](ulong &c) {
            ++c;
            return QChar(gc());
        };//case 0

    case 1: {
        ByteOrder bo = extr::getBOM(gc, count);

        switch (bo) {
        case littleEndian: return [_uchar](ulong &c) {
                return extr::getUtf16(_uchar, c, false);
            };//byte order is little endian

        case bigEndian: return [_uchar](ulong &c) {
                return extr::getUtf16(_uchar, c, true);
            };//byte order is big endian

        case none: {
            correct = false;
            return [](ulong&) {
                return QChar();
            };
        }//no byte order found
        }//switch (byte order)
    }//case 1

    case 2: return [_uchar](ulong &c) {
            return extr::getUtf16(_uchar, c, true);
        };//case 2

    case 3: return [_uchar](ulong &c) {
            return extr::getUtf8(_uchar, c);
        };//case 3

    default: {
        correct = false;
        return [](ulong&) {
            return QChar();
        };
    }//default

    }//switch (mark)
}

template <typename T, class>//V2 unsynch
std::function<QChar(ulong&)> extr::getFunctionV2(std::function<T()> gc, bool unsynch,
                            std::function<void()> back, bool &correct, ulong &count) {
    if (unsynch) {
        T mark = extr::getUns(gc, unsynch, back, count);
        std::function<uchar()> _uchar = [gc] {
            return toUchar(gc());
        };

        switch (mark) {
        case 0: return [_uchar, unsynch, back](ulong &c) {
                return extr::getUns(_uchar, unsynch, back, c);
            };//case 0

        case 1: return [_uchar, unsynch, back](ulong &c) {
                return extr::getUcs2(_uchar, unsynch, back, c);
            };//case 1

        default: {
            correct = false;
            return [](ulong&) {
                return QChar();
            };
        }//default

        }//switch (mark)
    }
    else {
        return extr::getFunctionV2(gc, correct, count);
    }
}

template <typename T, class>//V3 unsynch
std::function<QChar(ulong&)> extr::getFunctionV3(std::function<T()> gc, bool unsynch,
                            std::function<void()> back, bool &correct, ulong &count) {
    if (unsynch) {
        qDebug() << "getFunction for V3 with unsynch: called\n";
        T mark = extr::getUns(gc, unsynch, back, count);
        std::function<uchar()> _uchar = [gc] {
            return toUchar(gc());
        };

        switch (mark) {
        case 0: return [gc, unsynch, back] (ulong &c) {
                return extr::getUns(gc, unsynch, back, c);
            };//case 0

        case 1: {
            ByteOrder bo = extr::getBOM(_uchar, count);

            switch (bo) {
            case littleEndian: return [_uchar, unsynch, back](ulong &c)-> QChar {
                    return extr::getUcs2(_uchar, unsynch, back, c, false);
                };//ByteOrder = littleEndian

            case bigEndian: return [_uchar, unsynch, back](ulong &c)-> QChar {
                    return extr::getUcs2(_uchar, unsynch, back, c, true);
                };//ByteOrder = bigEndian

            case none: {
                correct = false;
                return [](ulong&) {
                    return QChar();
                };
            }//ByteOrder = none

            }//switch ByteOrder
        }//case 1

        default: {
            correct = false;
            return [](ulong&) {
                return QChar();
            };
        }//default

        }//switch (mark)
    }
    else {
        return extr::getFunctionV3(gc, correct, count);
    }
}

template <typename T, class>//V4 unsynch
std::function<QChar(ulong&)> extr::getFunctionV4(std::function<T()> gc, bool unsynch,
                            std::function<void()> back, bool &correct, ulong &count) {
    if (unsynch) {
        T mark = extr::getUns(gc, unsynch, back, count);
        qDebug() << "getFunctionV4 with unsynch, mark =" << int(mark) << endl;
        std::function<uchar()> _uchar = [gc] {
            return toUchar(gc());
        };

        switch (mark) {
        case 0: return [gc, unsynch, back](ulong &c) {
                return extr::getUns(gc, unsynch, back, c);
            };//case 0

        case 1: {
            ByteOrder bo = extr::getBOM(_uchar, unsynch, back, count);

            switch (bo)
            {
            case littleEndian: return [_uchar, unsynch, back](ulong &c) {
                    return extr::getUtf16(_uchar, unsynch, back, c, false);
                };//ByteOrder = little endian

            case bigEndian: return [_uchar, unsynch, back](ulong &c) {
                    return extr::getUtf16(_uchar, unsynch, back, c, true);
                };//ByteOrder = big endian

            case none: {
                correct = false;
                return [](ulong&) {
                    return QChar();
                };
            }//no BOM found
            }//switch (ByteOrder)
        }//case 1

        case 2: return [_uchar, unsynch, back](ulong &c) {
                return extr::getUtf16(_uchar, unsynch, back, c, true);
            };//case 2

        case 3: return [_uchar, unsynch, back](ulong &c) {
                return extr::getUtf8(_uchar, unsynch, back, c);
            };//case 3

        default: {
            correct = false;
            return [](ulong&) {
                return QChar();
            };
        }//default

        }//switch (mark)
    }
    else {
        qDebug() << "getFunctionV4: redirecting to getFunction without unsynch\n";
        return extr::getFunctionV4(gc, correct, count);
    }
}
