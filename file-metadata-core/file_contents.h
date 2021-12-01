#pragma once
#include "binary.h"
#include "easy_ptr.h"
using namespace std;

class FileContents
{
    void oneByteBack();

protected:
    QByteArray data{};
    ulong position{0};

    function<bool(char *)> getCharLambda{
                                            [this](char *c)
                                            {
                                                return this->getChar(c);
                                            }
                                        };

    function<void()> oneByteBackLambda{
                                            [this]()
                                            {
                                                return this->oneByteBack();
                                            }
                                      };

public:
    FileContents();

    bool setDataAndCheckSrc(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_crc);//file -> tag

    bool decompressRawData(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_data_size);//file -> frame

    bool decompressRawData(FileContents &other_storage, ulong raw_data_size, ulong expected_data_size);//tag -> frame

    QByteArray shareData(ulong size);

    bool getChar(char *);

    /*---<элементарные функции>---*/
    char ch();

    uchar get();

    template<typename T>
    char ch(T &);

    template<typename T>
    uchar get(T &);
    /*---</элементарные функции>---*/

    ByteOrder getBOM();

    QString getIso8859Str();

    QString getIso8859Str(const long long &);

    QString getUtf16Str(ByteOrder);//не чекает BOM

    QString getUtf16Str(ByteOrder, const long long &);//не чекает BOM

    QString getUtf8Str();

    QString getUtf8Str(const long long &);

    QString getUcs2Str(ByteOrder);//не чекает BOM

    QString getUcs2Str(ByteOrder, const long long &);//не чекает BOM

    QByteArray getBinaryTillEnd();

    StringEncoding getStringEncoding(TagVersion);

    QString getEncodingDependentString(TagVersion);

    QString getEncodingDependentString(TagVersion, const long long &);

    bool skip();

    ulong pos() const;

    void seek(ulong);

    void shift(long long = -1);

    bool end() const;

    int lastPos() const;

    int size() const;

    string getSymbols(int);

    string getFrame34Id();

    operator bool () const;

    virtual ~FileContents();
};

template<typename T>
char FileContents::ch(T &count)
{
    return ::ch(getCharLambda
                , count);
}

template<typename T>
uchar FileContents::get(T &count)
{
    return ::get(getCharLambda
                 , count);
}
