#pragma once
#include "binary.h"

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
    virtual char ch() const;
    virtual char uch() const;
    char ch(ulong &) const;
    char uch(ulong &) const;

    virtual uchar get() const;
    virtual uchar getb() const;
    uchar get(ulong &) const;
    uchar getb(ulong &) const;

    QString getEncodingDependentString(TagVersion) const;
    QString getEncodingDependentString(TagVersion, ulong) const;

    virtual QString getUrl() const;
    virtual QString getUrl(ulong) const;

    virtual std::vector<uchar> getBinaryTillEnd() const;
    virtual ulong get32Bit(ulong &count) const;
    virtual std::pair<uint, uint> getNumericPair(ulong len, char separator) const;
    QList<QString> getList(ulong len, TagVersion v, QChar separator) const;

    virtual bool skip() const;
    virtual long long pos() const;
    virtual void seek(long long) const;
    virtual void shift(long long = -1) const;
    virtual bool end() const;
    virtual long long size() const;

    ulong setLength(std::function<uchar(ulong &)>);
    bool setLength(std::function<uchar()>);
    void setLength(const uchar*);

    virtual std::string getSymbols(int);

    virtual bool parseHeader() = 0;
    virtual bool parseData() = 0;

public:
    explicit FileHolder(Binary &);//tag
    FileHolder(Binary &, bool);//frame

    virtual bool parse();

    const Binary &getFile() const;
    Binary &getFile();

    bool getUnsynch() const;

    operator bool () const;

    qint64 endpos() const;

    virtual ~FileHolder();
};
