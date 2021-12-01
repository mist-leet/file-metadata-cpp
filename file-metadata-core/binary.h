#pragma once
#include "new.h"
using namespace std;

//QFile с необходимыми расширениями
class Binary : public QFile
{
protected:
    bool finely_opened;

private:
    Binary(const Binary &) = delete;
    Binary& operator = (const Binary &) = delete;

protected:
    class V1;
    friend class V1;

    class V22;

    friend class V22;

    class V23;
    friend class V23;

    class V24;
    friend class V24;

public:
    enum byte_order {little_endian, big_endian, wrong};

    explicit Binary(const QString & path) :
        QFile(path)
    {
        finely_opened = open(QIODevice::ReadWrite | QIODevice::ExistingOnly);
    }

    unsigned char get();

    unsigned char getb(bool);

    template<typename T>
    unsigned char get(T & count)
    {
        ++count;
        return get();
    }

    template<typename T>
    unsigned char getb(T & count, bool unsynch)
    {
        unsigned char first = get(count);
        if (unsynch)
            if (get(count) != 0 || first != 255)
            {
                seek(pos() - 1);
                --count;
            }
        return first;
    }

    char ch();

    char _ch(bool);

    long get_utf8(bool);

    long get_utf16(bool unsynch, bool big_endian);

    long get_usc2(bool unsynch, bool big_endian);

    byte_order get_BOM(bool);

    operator bool () const;

    Binary & operator << (const string &);

    Binary & operator << (char);

    Binary & operator >> (char &);

    virtual ~Binary();
};
