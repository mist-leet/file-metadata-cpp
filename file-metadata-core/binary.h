#pragma once
#include "frame_structs.h"
#include "tag_structs.h"
#include "file_structs.h"
#include "char_extracting.h"
using namespace std;

class Binary : public QFile
{
    Binary(const Binary &) = delete;
    Binary& operator = (const Binary &) = delete;

    void oneByteBack();

protected:
    bool successfullyOpened{false};
    FileMetadata data{};

    function<bool(char *)> getCharLambda{
                                            [this](char * c)
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
    class V1;
    class V22;
    class V23;
    class V24;
    //friend class ::Parser;

    explicit Binary(const QString &);

    Binary();

    bool openf(const QString &);

    /*---<элементарные функции>---*/
    char ch();

    uchar get();

    char uch(bool);

    uchar getb(bool);

    template<typename T>
    char ch(T &);

    template<typename T>
    uchar get(T &);

    template<typename T>
    char uch(T &, bool);

    template<typename T>
    uchar getb(T &, bool);
    /*---</элементарные функции>---*/

    ByteOrder getBOM(bool);

    QString getIso8859Str(bool, const long long &);

    QString getUtf16Str(bool, ByteOrder, const long long &);//не чекает BOM

    QString getUtf8Str(bool, const long long &);

    QString getUcs2Str(bool, ByteOrder, const long long &);//не чекает BOM

    StringEncoding getStringEncoding(bool, TagVersion);

    QString getEncodingDependentString(bool, TagVersion, const long long &);

    QByteArray getBytes(bool, ulong);

    operator bool () const;

    const FileMetadata & getData() const;

    FileMetadata & getData();

    bool parse();

    void displayInfo(bool) const;

    bool hasInfo() const;

    void shift(long long = -1);

    void backFromEnd(qint64);

    char charBackwards();

    bool checkFor(string);

    TagVersion v2Header();

    ulong parseV2Footer();//возвращает 0, если футер не найден или некорректен

    void parseFromStart();

    void parseFromEnd();

    void parseV1();

    virtual ~Binary() override;
};

template<typename T>
uchar Binary::get(T & count)
{
    return ::get(getCharLambda
                , count);
}

template<typename T>
char Binary::ch(T & count)
{
    return ::ch(getCharLambda
                , count);
}

template<typename T>
uchar Binary::getb(T & count, bool unsynch)
{
    return ::getb(getCharLambda
                , unsynch
                , oneByteBackLambda
                , count);
}

template<typename T>
char Binary::uch(T & count, bool unsynch)
{
    return ::uch(getCharLambda
                , unsynch
                , oneByteBackLambda
                , count);
}
