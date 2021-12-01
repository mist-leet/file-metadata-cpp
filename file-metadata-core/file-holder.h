#pragma once
#include "binary.h"
using namespace std;

class File_holder
{
protected:
    Binary & file;
    bool unsynch;
    unsigned long length;
    long long start_position;
    long long end_position;//end position можно воспринимать как положение символа, следующего за последним символом File holder'а

private:
    File_holder(const File_holder &) = delete ;
    File_holder & operator = (const File_holder &) = delete ;

protected:
    unsigned char get() const;

    unsigned char getb() const;

    template<typename T>
    unsigned char get(T & count) const
    {
        return file.get(count);
    }

    template<typename T>
    unsigned char getb(T &count) const
    {
        return file.getb(count, unsynch);
    }

    char ch() const;

    char _ch() const;

    long get_utf8() const;

    long get_utf16(bool big_endian) const;

    long get_usc2(bool big_endian) const;

    bool seek(long long) const;

    long long pos() const;

    operator bool () const;

    void skip() const;

    explicit File_holder(Binary &);

    File_holder(Binary &, bool);
public:
    virtual ~File_holder() = default;
};
