#include "file_contents.h"
using std::vector;
using std::string;

FileContents::FileContents()
{}

FileContents::~FileContents() = default;

bool FileContents::setDataAndCheckSrc(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_crc) {
    arr = file.getBytes(unsynch,raw_data_size);
    ulong actual_size = size();
    ulong crc = crc32(0,nullptr,0);//инициализация crc
    crc = crc32(crc,arr.data(),actual_size);//могут быть ошибки;
    return crc == expected_crc;
}

char FileContents::ch(ulong &count) {
    ++count;
    return ch();
}

uchar FileContents::get(ulong &count) {
    ++count;
    return get();
}

bool FileContents::decompressRawData(Binary &file, bool unsynch, ulong raw_data_size,  ulong expected_data_size) {
    arr = Gl::uncompressWrapper(file.getBytes(unsynch,raw_data_size),expected_data_size);
    return !arr.empty();
}

bool FileContents::decompressRawData(FileContents &other_storage, ulong raw_data_size, ulong expected_data_size) {
    arr = Gl::uncompressWrapper(other_storage.shareData(raw_data_size),expected_data_size);
    return !arr.empty();
}

std::vector<uchar> FileContents::shareData(ulong size) {
    std::vector<uchar> newV;
    newV.reserve(arr.size());
    for (ulong i = 0;i < size;++i)
        newV.push_back(get());
    return newV;
}

bool FileContents::skip() {
    position = lastPos();
    return true;
}

ulong FileContents::pos() const {
    return position;
}

void FileContents::seek(ulong new_position) {
    if (new_position <= lastPos())
        position = new_position;
    else
        position = lastPos();
}

void FileContents::shift(long long offset) {
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

FileContents::operator bool () const {
    return !arr.empty();
}

bool FileContents::end() const {
    return position == arr.size();
}

ulong FileContents::lastPos() const {
    return arr.size() - 1;
}

ulong FileContents::size() const {
    return arr.size();
}

char FileContents::ch() {
    return toChar(get());
}

uchar FileContents::get() {
    if (position <= lastPos()) {
        ++position;
        return arr[position];
    }
    else
        return 0;
}

vector<uchar> FileContents::getBinaryTillEnd() {
    vector<uchar> v{};
    v.reserve(size() - position);
    while (!end())
        v.push_back(get());
    return v;
}

QString FileContents::getEncodingDependentString(TagVersion v) {
    return extr::getEncodingDependentString(getLambda, size() - position, v);
}

QString FileContents::getEncodingDependentString(TagVersion v, ulong len) {
    return extr::getEncodingDependentString(getLambda, len, v);
}

QString FileContents::getUrl() {
    return extr::getUrl(getLambda, size() - position);
}

QString FileContents::getUrl(ulong len) {
    return extr::getUrl(getLambda, len);
}

ulong FileContents::get32Bit(ulong &count) {
    return extr::get32Bit(getLambda, count);
}

std::pair<uint, uint> FileContents::getNumericPair(ulong len, uchar separator) {
    return extr::getNumericPair(getLambda, len, separator);
}

QList<QString> FileContents::getList(ulong len, TagVersion v, QChar separator) {
    return extr::getList(getLambda, len, v, separator);
}

string FileContents::getSymbols(int amount) {
    string str;
    for (int i = 0;i < amount;++i)
        str += ch();
    return str;
}

string FileContents::getFrame34Id() {
    return getSymbols(4);
}
