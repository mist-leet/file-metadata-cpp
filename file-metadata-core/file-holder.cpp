#include "file-holder.h"
using namespace std;

FileHolder::FileHolder(Binary &f)//tag
    : file(f)
    , unsynch(false)
    , synchsafeHeader(true)
    , startPosition(file.pos() - 5)
    , endPosition(startPosition + 3)
    {}

FileHolder::FileHolder(Binary &f, bool u)//frame
    : file(f)
    , unsynch(u)
    , synchsafeHeader(false)
    , startPosition(file.pos() - 4)
    , endPosition(startPosition + 4)
    {}

FileHolder::~FileHolder() = default;

pair<int, bool> FileHolder::setLength(function<uchar(int &)> get_f)
{
    uchar bytes[4];
    int count = 0;
    for (int i = 3;i >= 0;--i)
    {
        bytes[i] = get_f(count);
        if (synchsafeHeader && bytes[i] > 127)
            return make_pair(count,false);
    }

    ulong factor;
    if (synchsafeHeader)
        factor = 128;
    else
        factor = 256;

    for (int i = 3;i >= 0;--i)
        length += static_cast<ulong>(bytes[i])*power(factor,i);

    return make_pair(count,true);
}

FileHolder::operator bool() const
{
    return pos() < endPosition;
}

long long FileHolder::size() const
{
    return file.size();
}

bool FileHolder::end() const
{
    return pos() == endPosition;
}

void FileHolder::seek(long long pos) const
{
    if (pos >= 0 && pos < file.size())
        file.seek(pos);
    else
    {
        if (pos < 0)
            file.seek(0);
        else
            file.seek(size() - 1);
    }
}

long long FileHolder::pos() const
{
    return file.pos();
}

bool FileHolder::skip() const
{
    seek(endPosition);
    return true;
}

void FileHolder::shift(long long offset) const
{
    long long resulting_pos = pos() + offset;
    seek(resulting_pos);
}

bool FileHolder::parse()
{
    if (parseHeader())
        return parseData();
    else
        return !skip();
}

const Binary & FileHolder::getFile() const
{
    return file;
}

Binary & FileHolder::getFile()
{
    return file;
}

bool FileHolder::getUnsynch() const
{
    return unsynch;
}

char FileHolder::ch() const
{
    return file.ch();
}

uchar FileHolder::get() const
{
    return file.get();
}

char FileHolder::uch() const
{
    return file.uch(unsynch);
}

uchar FileHolder::getb() const
{
    return file.getb(unsynch);
}

ByteOrder FileHolder::getBOM() const
{
    return file.getBOM(unsynch);
}

QString FileHolder::getIso8859Str() const
{
    return file.getIso8859Str(unsynch, endPosition - pos());
}

QString FileHolder::getIso8859Str(const long long &dur) const
{
    return file.getIso8859Str(unsynch, dur);
}

QString FileHolder::getUtf16Str(ByteOrder bo) const//не чекает BOM
{
    return file.getUtf16Str(unsynch, bo, endPosition - pos());
}

QString FileHolder::getUtf16Str(ByteOrder bo, const long long &dur) const//не чекает BOM
{
    return file.getUtf16Str(unsynch, bo, dur);
}

QString FileHolder::getUtf8Str() const
{
    return file.getUtf8Str(unsynch, endPosition - pos());
}

QString FileHolder::getUtf8Str(const long long &dur) const
{
    return file.getUtf8Str(unsynch, dur);
}

QString FileHolder::getUcs2Str(ByteOrder bo) const//не чекает BOM
{
    return file.getUcs2Str(unsynch, bo, endPosition - pos());
}

QString FileHolder::getUcs2Str(ByteOrder bo, const long long &dur) const//не чекает BOM
{
    return file.getUcs2Str(unsynch, bo, dur);
}

StringEncoding FileHolder::getStringEncoding(TagVersion v)
{
    return file.getStringEncoding(unsynch, v);
}

QString FileHolder::getEncodingDependentString(TagVersion v) const
{
    return file.getEncodingDependentString(unsynch, v, endPosition - pos());
}

QString FileHolder::getEncodingDependentString(TagVersion v, const long long &dur) const
{
    return file.getEncodingDependentString(unsynch, v, dur);
}

QByteArray FileHolder::getBinaryTillEnd() const
{
    QByteArray arr;
    while (*this)
        arr.append(uch());
    return arr;
}

string FileHolder::getSymbols(int amount)
{
    string str;
    for (int i = 0;i < amount;++i)
        str += uch();
    return str;
}

qint64 FileHolder::endpos() const
{
    return endPosition;
}
