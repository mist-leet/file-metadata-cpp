#include "file_contents.h"
using namespace std;

FileContents::FileContents()
{}

FileContents::~FileContents() = default;

bool FileContents::setDataAndCheckSrc(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_crc)
{
    data = file.getBytes(unsynch,raw_data_size);
    uint actual_size = data.size();
    EasyPtr<uchar> unsigned_data(actual_size);
    toUchar(data.constData(),unsigned_data.getPtr(),actual_size);
    ulong crc = crc32(0,nullptr,0);//инициализация crc
    crc = crc32(crc,unsigned_data.constPtr(),actual_size);//могут быть ошибки
    return crc == expected_crc;
}

bool FileContents::decompressRawData(Binary &file, bool unsynch, ulong raw_data_size,  ulong expected_data_size)
{
    data = qUncompressWrapper(file.getBytes(unsynch,raw_data_size),expected_data_size);
    return !data.isEmpty();
}

bool FileContents::decompressRawData(FileContents &other_storage, ulong raw_data_size, ulong expected_data_size)
{
    data = qUncompressWrapper(other_storage.shareData(raw_data_size),expected_data_size);
    return !data.isEmpty();
}

QByteArray FileContents::shareData(ulong size)
{
    QByteArray arr;
    for (ulong i = 0;i < size;++i)
        arr.append(ch());
    return arr;
}

void FileContents::oneByteBack()
{
    --position;
}

bool FileContents::getChar(char * c)
{
    if (c)
    {
        if (position <= lastPos())
        {
            *c = data.at(position);
            ++position;
        }
        else
            *c = 0;
    }
    return c;
}

bool FileContents::skip()
{
    position = lastPos();
    return true;
}

ulong FileContents::pos() const
{
    return position;
}

void FileContents::seek(ulong new_position)
{
    if (new_position <= lastPos())
        position = new_position;
    else
        position = lastPos();
}

void FileContents::shift(long long offset)
{
    long long resulting_pos = position + offset;
    if (resulting_pos >= 0 && resulting_pos <= lastPos())
        position = resulting_pos;
    else
    {
        if (resulting_pos < 0)
            position = 0;
        else
            position = lastPos();
    }
}

FileContents::operator bool () const
{
    return !data.isEmpty();
}

bool FileContents::end() const
{
    return position == data.size();
}

int FileContents::lastPos() const
{
    return data.size() - 1;
}

int FileContents::size() const
{
    return data.size();
}

char FileContents::ch()
{
    return ::ch(getCharLambda);
}

uchar FileContents::get()
{
    return ::get(getCharLambda);
}

ByteOrder FileContents::getBOM()
{
    return ::getBOM(getCharLambda,false,oneByteBackLambda);
}

QString FileContents::getIso8859Str()
{
    return ::getIso8859Str(getCharLambda,false,oneByteBackLambda,data.size() - position);
}

QString FileContents::getIso8859Str(const long long & len)
{
    return ::getIso8859Str(getCharLambda,false,oneByteBackLambda,len);
}

QString FileContents::getUtf16Str(ByteOrder bo)//не чекает BOM
{
    return ::getUtf16Str(getCharLambda,false,bo,oneByteBackLambda,data.size() - position);
}

QString FileContents::getUtf16Str(ByteOrder bo, const long long & len)//не чекает BOM
{
    return ::getUtf16Str(getCharLambda,false,bo,oneByteBackLambda,len);
}

QString FileContents::getUtf8Str()
{
    return ::getUtf8Str(getCharLambda,false,oneByteBackLambda,data.size() - position);
}

QString FileContents::getUtf8Str(const long long & len)
{
    return ::getUtf8Str(getCharLambda,false,oneByteBackLambda,len);
}

QString FileContents::getUcs2Str(ByteOrder bo)//не чекает BOM
{
    return ::getUcs2Str(getCharLambda,false,bo,oneByteBackLambda,data.size() - position);
}

QString FileContents::getUcs2Str(ByteOrder bo, const long long & len)//не чекает BOM
{
    return ::getUcs2Str(getCharLambda,false,bo,oneByteBackLambda,len);
}

QByteArray FileContents::getBinaryTillEnd()
{
    QByteArray arr;
    while (!end())
        arr.append(ch());
    return arr;
}

StringEncoding FileContents::getStringEncoding(TagVersion v)
{
    return ::getStringEncoding(getCharLambda, false, oneByteBackLambda, v);
}

QString FileContents::getEncodingDependentString(TagVersion v)
{
    return ::getEncodingDependentString(getCharLambda, false, oneByteBackLambda, data.size() - position,
                                           getStringEncoding(v));
}

QString FileContents::getEncodingDependentString(TagVersion v, const long long &len)
{
    return ::getEncodingDependentString(getCharLambda, false, oneByteBackLambda, len,
                                           getStringEncoding(v));
}

string FileContents::getSymbols(int amount)
{
    string str;
    for (int i = 0;i < amount;++i)
        str += ch();
    return str;
}

string FileContents::getFrame34Id()
{
    return getSymbols(4);
}
