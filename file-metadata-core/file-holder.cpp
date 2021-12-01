#include "file-holder.h"
using std::string;
using std::vector;

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

ulong FileHolder::setLength(std::function<uchar(ulong &)> get_f) {
    uchar bytes[4];
    ulong count = 0;
    for (int i = 3;i >= 0;--i) {
        bytes[i] = get_f(count);
        if (synchsafeHeader && bytes[i] > 127)
            return count;
    }

    setLength(bytes);
    return count;
}

bool FileHolder::setLength(std::function<uchar ()> get_f) {
    uchar bytes[4];

    for (int i = 3;i >= 0;--i) {
        bytes[i] = get_f();
        if (synchsafeHeader && bytes[i] > 127)
            return false;
    }

    setLength(bytes);
    return true;
}

void FileHolder::setLength(const uchar *bytes) {
    uint factor;
    if (synchsafeHeader)
        factor = 128;
    else
        factor = 256;

    for (int i = 3;i >= 0;--i)
        length += static_cast<ulong>(bytes[i])*power(factor,i);

uchar FileHolder::get(ulong &count) const {
    return file.get(count);
}

char FileHolder::uch(ulong &count) const {
    return file.uch(count, unsynch);
}

uchar FileHolder::getb(ulong &count) const {
    return file.getb(count, unsynch);
}

FileHolder::operator bool() const {
    return pos() < endPosition;
}

long long FileHolder::size() const {
    return file.size();
}

bool FileHolder::end() const {
    return pos() == endPosition;
}

void FileHolder::seek(long long pos) const {
    if (pos >= 0 && pos < file.size())
        file.seek(pos);
    else {
        if (pos < 0)
            file.seek(0);
        else
            file.seek(size() - 1);
    }
}

long long FileHolder::pos() const {
    return file.pos();
}

bool FileHolder::skip() const {
    seek(endPosition);
    return true;
}

void FileHolder::shift(long long offset) const {
    seek(pos() + offset);
}

bool FileHolder::parse() {
    qDebug() << "FileHolder: starting to parse" << ::end;
    if (parseHeader())
        return parseData();
    else
        return !skip();
}

const Binary & FileHolder::getFile() const {
    return file;
}

Binary & FileHolder::getFile() {
    return file;
}

bool FileHolder::getUnsynch() const {
    return unsynch;
}

char FileHolder::ch() const {
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

QString FileHolder::getEncodingDependentString(TagVersion v) const {
    //qDebug() << "FileHolder: getting encoding dependent string for tag" << v << ::end;
    return file.getEncodingDependentString(unsynch, v, endPosition - pos());
}

QString FileHolder::getEncodingDependentString(TagVersion v, ulong len) const {
    return file.getEncodingDependentString(unsynch, v, len);
}

QString FileHolder::getUrl() const {
    return file.getUrl(unsynch, endPosition - pos());
}

QString FileHolder::getUrl(ulong len) const {
    return file.getUrl(unsynch, len);
}

vector<uchar> FileHolder::getBinaryTillEnd() const {
    vector<uchar> v{};
    v.reserve(endPosition - pos());//
    if (unsynch) {
        while (*this)
            v.push_back(getb());
    }
    else {
        while (*this)
            v.push_back(get());
    }
    return v;
}

QList<QString> FileHolder::getList(ulong len, TagVersion v, QChar separator) const {
    return file.getList(unsynch, v, len, separator);
}

ulong FileHolder::get32Bit(ulong &count) const {
    return file.get32Bit(unsynch, count);
}

std::pair<uint, uint> FileHolder::getNumericPair(ulong len, char separator) const {
    return file.getNumericPair(unsynch, len, separator);
}

string FileHolder::getSymbols(int amount) {
    string str;
    for (int i = 0;i < amount;++i)
        str += uch();
    return str;
}

qint64 FileHolder::endpos() const {
    return endPosition;
}
