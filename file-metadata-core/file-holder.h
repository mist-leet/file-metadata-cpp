#pragma once
#include "binary.h"
using namespace std;

class File_holder
{
protected:
    Binary &file;
    bool unsynch;
    bool synchsafe_header;
    ulong length{0};//start_position + length < end_position , так как length не учитывает хедер
    long long start_position;
    long long end_position;//номер символа, следующего за последним символом File holder'а

private:
    File_holder(const File_holder &) = delete;
    File_holder & operator = (const File_holder &) = delete;

protected:
    /*---<элементарные функции>---*/
    virtual char ch() const;

    virtual uchar get() const;

    virtual char uch() const;

    virtual uchar getb() const;

    template<typename T>
    char ch(T &) const;

    template<typename T>
    uchar get(T &) const;

    template<typename T>
    char uch(T &) const;

    template<typename T>
    uchar getb(T &) const;
    /*---</элементарные функции>---*/

    virtual Byte_order get_BOM() const;

    virtual QString get_iso8859_str() const;

    virtual QString get_iso8859_str(const long long &) const;

    virtual QString get_utf16_str(Byte_order) const;//не чекает BOM

    virtual QString get_utf16_str(Byte_order, const long long &) const;//не чекает BOM

    virtual QString get_utf8_str() const;

    virtual QString get_utf8_str(const long long &) const;

    virtual QString get_ucs2_str(Byte_order) const;//не чекает BOM

    virtual QString get_ucs2_str(Byte_order, const long long &) const;//не чекает BOM

    virtual QString get_encoding_dependent_string(String_encoding) const;

    virtual QString get_encoding_dependent_string(String_encoding, const long long &) const;

    virtual QByteArray get_binary_till_end() const;

    virtual bool skip() const;

    virtual long long pos() const;

    virtual void seek(long long) const;

    virtual void shift(long long = -1) const;

    virtual bool end() const;

    virtual long long size() const;

    pair<int,bool> set_length(function<uchar(int &)>);

    virtual string get_symbols(int);

    virtual bool parse_header() = 0;

    virtual bool parse_data() = 0;

public:
    explicit File_holder(Binary &);//tag

    File_holder(Binary &, bool);//frame

    virtual bool parse();

    const Binary & get_file() const;

    Binary & get_file();

    bool get_unsynch() const;

    operator bool () const;

    qint64 endpos() const;

    virtual ~File_holder();
};

template<typename T>
char File_holder::ch(T &count) const
{
    return file.ch(count);
}

template<typename T>
uchar File_holder::get(T &count) const
{
    return file.get(count);
}

template<typename T>
char File_holder::uch(T &count) const
{
    return file.uch(count, unsynch);
}

template<typename T>
uchar File_holder::getb(T &count) const
{
    return file.getb(count, unsynch);
}
