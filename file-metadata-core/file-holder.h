#pragma once
#include "binary.h"
using namespace std;

class FileHolder
{
protected:
    Binary &file;
    bool unsynch;
    bool synchsafeHeader;
    ulong length{0};//startPosition + length < endPosition , так как length не учитывает хедер
    long long startPosition;
    long long endPosition;//номер символа, следующего за последним символом FileHolder'а

private:
    FileHolder(const FileHolder &) = delete;
    FileHolder & operator = (const FileHolder &) = delete;

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

    virtual ByteOrder getBOM() const;

    virtual QString getIso8859Str() const;

    virtual QString getIso8859Str(const long long &) const;

    virtual QString getUtf16Str(ByteOrder) const;//не чекает BOM

    virtual QString getUtf16Str(ByteOrder, const long long &) const;//не чекает BOM

    virtual QString getUtf8Str() const;

    virtual QString getUtf8Str(const long long &) const;

    virtual QString getUcs2Str(ByteOrder) const;//не чекает BOM

    virtual QString getUcs2Str(ByteOrder, const long long &) const;//не чекает BOM

    StringEncoding getStringEncoding(TagVersion);

    QString getEncodingDependentString(TagVersion) const;

    QString getEncodingDependentString(TagVersion, const long long &) const;

    virtual QByteArray getBinaryTillEnd() const;

    virtual bool skip() const;

    virtual long long pos() const;

    virtual void seek(long long) const;

    virtual void shift(long long = -1) const;

    virtual bool end() const;

    virtual long long size() const;

    pair<int,bool> setLength(function<uchar(int &)>);

    virtual string getSymbols(int);

    virtual bool parseHeader() = 0;

    virtual bool parseData() = 0;

public:
    explicit FileHolder(Binary &);//tag

    FileHolder(Binary &, bool);//frame

    virtual bool parse();

    const Binary & getFile() const;

    Binary & getFile();

    bool getUnsynch() const;

    operator bool () const;

    qint64 endpos() const;

    virtual ~FileHolder();
};

template<typename T>
char FileHolder::ch(T &count) const
{
    return file.ch(count);
}

template<typename T>
uchar FileHolder::get(T &count) const
{
    return file.get(count);
}

template<typename T>
char FileHolder::uch(T &count) const
{
    return file.uch(count, unsynch);
}

template<typename T>
uchar FileHolder::getb(T &count) const
{
    return file.getb(count, unsynch);
}
