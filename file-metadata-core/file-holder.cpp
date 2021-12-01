#include "file-holder.h"
using namespace std;

File_holder::File_holder(Binary & f)//tag
    : file(f)
    , unsynch(false)
    , synchsafe_header(true)
    , start_position(file.pos() - 5)
    , end_position(start_position + 3)
    {}

File_holder::File_holder(Binary & f, bool unsynch_)//frame
    : file(f)
    , unsynch(unsynch_)
    , synchsafe_header(false)
    , start_position(file.pos() - 4)
    , end_position(start_position + 4)
    {}

File_holder::~File_holder() = default;

pair<int, bool> File_holder::set_length(function<uchar(int &)> get_f)
{
    uchar bytes[4];
    int count = 0;
    for (int i = 3;i >= 0;--i)
    {
        bytes[i] = get_f(count);
        if (synchsafe_header && bytes[i] > 127)
            return make_pair(count,false);
    }

    ulong factor;
    if (synchsafe_header)
        factor = 128;
    else
        factor = 256;

    for (int i = 3;i >= 0;--i)
        length += static_cast<ulong>(bytes[i])*power(factor,i);

    return make_pair(count,true);
}

File_holder::operator bool() const
{
    return pos() < end_position;
}

long long File_holder::size() const
{
    return file.size();
}

bool File_holder::end() const
{
    return pos() == end_position;
}

void File_holder::seek(long long pos) const
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

long long File_holder::pos() const
{
    return file.pos();
}

bool File_holder::skip() const
{
    seek(end_position);
    return true;
}

void File_holder::shift(long long offset) const
{
    long long resulting_pos = pos() + offset;
    seek(resulting_pos);
}

bool File_holder::parse()
{
    if (parse_header())
        return parse_data();
    else
        return !skip();
}

const Binary & File_holder::get_file() const
{
    return file;
}

Binary & File_holder::get_file()
{
    return file;
}

bool File_holder::get_unsynch() const
{
    return unsynch;
}

char File_holder::ch() const
{
    return file.ch();
}

uchar File_holder::get() const
{
    return file.get();
}

char File_holder::uch() const
{
    return file.uch(unsynch);
}

uchar File_holder::getb() const
{
    return file.getb(unsynch);
}

Byte_order File_holder::get_BOM() const
{
    return file.get_BOM(unsynch);
}

QString File_holder::get_iso8859_str() const
{
    return file.get_iso8859_str(unsynch, end_position - pos());
}

QString File_holder::get_iso8859_str(const long long &dur) const
{
    return file.get_iso8859_str(unsynch, dur);
}

QString File_holder::get_utf16_str(Byte_order bo) const//не чекает BOM
{
    return file.get_utf16_str(unsynch, bo, end_position - pos());
}

QString File_holder::get_utf16_str(Byte_order bo, const long long &dur) const//не чекает BOM
{
    return file.get_utf16_str(unsynch, bo, dur);
}

QString File_holder::get_utf8_str() const
{
    return file.get_utf8_str(unsynch, end_position - pos());
}

QString File_holder::get_utf8_str(const long long &dur) const
{
    return file.get_utf8_str(unsynch, dur);
}

QString File_holder::get_ucs2_str(Byte_order bo) const//не чекает BOM
{
    return file.get_ucs2_str(unsynch, bo, end_position - pos());
}

QString File_holder::get_ucs2_str(Byte_order bo, const long long &dur) const//не чекает BOM
{
    return file.get_ucs2_str(unsynch, bo,dur);
}

QString File_holder::get_encoding_dependent_string(String_encoding enc) const
{
    return get_encoding_dependent_string(enc, end_position - pos());
}

QString File_holder::get_encoding_dependent_string(String_encoding enc, const long long &dur) const
{
    return file.get_encoding_dependent_string(unsynch, enc,dur,[this]()
                                                                {
                                                                    return this->skip();
                                                                });
}

QByteArray File_holder::get_binary_till_end() const
{
    QByteArray arr;
    while (*this)
        arr.append(uch());
    return arr;
}

string File_holder::get_symbols(int amount)
{
    string str;
    for (int i = 0;i < amount;++i)
        str += uch();
    return str;
}

qint64 File_holder::endpos() const
{
    return end_position;
}
