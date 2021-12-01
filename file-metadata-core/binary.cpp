#include "v24.h"
#include "v1.h"
using namespace std;

Binary::Binary(const QString &path)
    : QFile(path)
{
    successfullyOpened = QFile::open(QIODevice::ReadWrite | QIODevice::ExistingOnly);
    if (successfullyOpened)
        seek(0);
}

Binary::Binary()
    : QFile()
{}

Binary::~Binary()
{
    close();
}

bool Binary::openf(const QString &path)
{
    setFileName(path);
    successfullyOpened = QFile::open(QIODevice::ReadWrite | QIODevice::ExistingOnly);
    if (successfullyOpened)
        seek(0);
    return successfullyOpened;
}

Binary::operator bool() const
{
    return successfullyOpened;
}

Binary & Binary::operator << (const string & s)
{
    write(s.c_str(),s.size());
    return *this;
}

Binary & Binary::operator << (char c)
{
    write(&c,1);
    return *this;
}

Binary & Binary::operator >> (char & c)
{
    getChar(&c);
    return *this;
}

const FileMetadata & Binary::getData() const
{
    return data;
}

FileMetadata & Binary::getData()
{
    return data;
}

bool Binary::hasInfo() const
{
    return data.hasInfo();
}

void Binary::shift(long long offset)
{
    long long destination = pos() + offset;

    if (destination >=0 || destination < size())
        seek(destination);
    else
    {
        if (destination < 0)
            seek(0);
        else
            seek(size() - 1);
    }
}

void Binary::oneByteBack()
{
    seek(pos() - 1);
}

QByteArray Binary::getBytes(bool unsynch, ulong amount)
{
    return ::getBytes(getCharLambda
                           , unsynch
                           , oneByteBackLambda
                           , amount);
}

QByteArray Binary::get_bytes(bool unsynch, ulong amount)
{
    return ::get_bytes(getChar_lambda
                        , unsynch
                        , one_byte_back_lambda
                        , amount);
}

char Binary::ch()
{
    return ::ch(getCharLambda);
}

uchar Binary::get()
{
    return ::get(getCharLambda);
}

char Binary::uch(bool unsynch)
{
    return ::uch(getCharLambda
                 , unsynch
                 , oneByteBackLambda);
}

uchar Binary::getb(bool unsynch)
{
    return ::getb(getCharLambda
                  , unsynch
                  , oneByteBackLambda);
}

ByteOrder Binary::getBOM(bool unsynch)
{
    return ::getBOM(getCharLambda
                     , unsynch
                     , oneByteBackLambda);
}

QString Binary::getIso8859Str(bool unsynch, const long long &dur)
{
    return ::getIso8859Str(getCharLambda
                             , unsynch
                             , oneByteBackLambda
                             , dur);
}

QString Binary::getUtf16Str(bool unsynch, ByteOrder bo, const long long &dur)//не чекает BOM
{
    return ::getUtf16Str(getCharLambda
                           , unsynch
                           , bo
                           , oneByteBackLambda
                           , dur);
}

QString Binary::getUtf8Str(bool unsynch, const long long &dur)
{
    return ::getUtf8Str(getCharLambda
                          , unsynch
                          , oneByteBackLambda
                          , dur);
}

QString Binary::getUcs2Str(bool unsynch, ByteOrder bo, const long long &dur)//не чекает BOM
{
    return ::getUcs2Str(getCharLambda
                          , unsynch
                          , bo
                          , oneByteBackLambda
                          , dur);
}

QString Binary::getEncodingDependentString(bool unsynch, TagVersion v, const long long &dur)
{
    return ::getEncodingDependentString(getCharLambda, unsynch, oneByteBackLambda, dur,
                                           getStringEncoding(unsynch,v));
}

void Binary::parseFromStart()
{
    seek(0);
    TagVersion v;
    do
    {
        v = v2Header();
        Parser v2(v,*this);
        v2.parse();
    } while (v != noTag);
}

void Binary::parseFromEnd()
{
    backFromEnd(128);//перемещаемся на место предполагаемого тега v1
    if (checkFor("TAG"))//перемещаемся на место предполагаемого футера
        backFromEnd(138);
    else
        backFromEnd(10);

    TagVersion v;
    qint64 len = 0;

    do
    {
        len = parseV2Footer();//чекаем длину предполагаемого тега
        shift(-len - 20);//перемещаемся в начало предполагаемого тега
        v = v2Header();//чекаем идентификатор хедера предполагаемого тега
        Parser v2(v,*this);//создаём парсер для предполагаемого тега
        v2.parse();//парсим, если есть что парсить
        shift(-len - 20);//перемещаемся в место, где начинается футер предыдущего тега, если он есть
    } while (v != noTag);
}

void Binary::parseV1()
{
    if (data.needsV1())
    {
        backFromEnd(128);//перемещаемся на место предполагаемого тега v1
        if (checkFor("TAG"))
        {
            Parser v1(*this);
            v1.parse();
        }
    }
}

StringEncoding Binary::getStringEncoding(bool unsynch, TagVersion v)
{
    return ::getStringEncoding(getCharLambda, unsynch, oneByteBackLambda, v);
}

bool Binary::parse()
{
    if (successfullyOpened)
    {
        parseFromStart();
        parseFromEnd();
        parseV1();
        return data.hasInfo();
    }
    else
        return false;
}

void Binary::displayInfo(bool console) const
{
    if (console)
        data.displayOnConsole();
    else
        data.displayOnUi();
}

void Binary::backFromEnd(qint64 offset)
{
    qint64 sz = size();
    if (offset <= sz)
        seek(sz - offset);
    else
        seek(0);
}

char Binary::charBackwards()
{
    char c;
    getChar(&c);
    shift(-2);
    return c;
}

bool Binary::checkFor(string value)
{
    char id[4];
    for (int i = 0;i < 3;++i)
        getChar(id + i);
    id[3] = 0;
    return !strcmp(id,value.c_str());
}

TagVersion Binary::v2Header()
{
    if (checkFor("ID3"))
    {
        uchar version = get();
        if (get() != 255)
        {
            switch (version)
            {
            case 2:{return two;}
            case 3:{return three;}
            case 4:{return four;}
            default:{return noTag;}
            }
        }
        else
            return noTag;
    }
    else
        return noTag;
}

ulong Binary::parseV2Footer()//возвращает 0, если футер не найден или некорректен
{
    if (checkFor("3DI"))
    {
        if (get() == 4)
        {
            if (get() != 255)
            {
                mByte flags = get();
                if (!flags[4])//если в футере указано, что футера нет
                    return 0;
                for (uint i = 0;i < 4;++i)
                    if (flags[i])//если проставлены неопределённые флаги
                        return 0;

                ulong len = 0;
                uchar c;
                for (int i = 3;i >= 0;--i)
                {
                    c = get();
                    if (c > 127)//выставлен msb
                        return 0;
                    else
                        len += c*power(128,i);
                }
                return len;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}
