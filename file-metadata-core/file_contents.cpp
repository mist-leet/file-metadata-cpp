#include "file_contents.h"
using namespace std;

File_contents::File_contents()
    : data()
{}

File_contents::~File_contents() = default;

bool File_contents::set_data_and_check_src(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_crc)
{
    data = file.get_raw_bytes(unsynch,raw_data_size);
    uint actual_size = data.size();
    Easy_ptr<uchar> unsigned_data(actual_size);
    to_uchar(data.constData(),unsigned_data.get_ptr(),actual_size);
    ulong crc = crc32(0,nullptr,0);//инициализация crc
    crc = crc32(crc,unsigned_data.const_ptr(),actual_size);//могут быть ошибки
    return crc == expected_crc;
}

bool File_contents::decompress_raw_data(Binary &file, bool unsynch, ulong raw_data_size,  ulong expected_data_size)
{
    data = qUncompressWrapper(file.get_raw_bytes(unsynch,raw_data_size),expected_data_size);
    return !data.isEmpty();
}

bool File_contents::decompress_raw_data(File_contents &other_storage, ulong raw_data_size, ulong expected_data_size)
{
    data = qUncompressWrapper(other_storage.share_data(raw_data_size),expected_data_size);
    return !data.isEmpty();
}

QByteArray File_contents::share_data(ulong size)
{
    QByteArray arr;
    for (ulong i = 0;i < size;++i)
        arr.append(ch());
    return arr;
}

void File_contents::one_byte_back_with_no_check()
{
    --position;
}

bool File_contents::getChar(char * c)
{
    if (c)
    {
        if (position <= lastpos())
        {
            *c = data.at(position);
            ++position;
        }
        else
            *c = 0;
    }
    return c;
}

bool File_contents::skip()
{
    position = lastpos();
    return true;
}

ulong File_contents::pos() const
{
    return position;
}

void File_contents::seek(ulong new_position)
{
    if (new_position <= lastpos())
        position = new_position;
    else
        position = lastpos();
}

void File_contents::shift(long long offset)
{
    long long resulting_pos = position + offset;
    if (resulting_pos >= 0 && resulting_pos <= lastpos())
        position = resulting_pos;
    else
    {
        if (resulting_pos < 0)
            position = 0;
        else
            position = lastpos();
    }
}

File_contents::operator bool () const
{
    return !data.isEmpty();
}

bool File_contents::end() const
{
    return position == data.size();
}

int File_contents::lastpos() const
{
    return data.size() - 1;
}

int File_contents::size() const
{
    return data.size();
}

char File_contents::ch()
{
    return ::ch(getCharLambda);
}

uchar File_contents::get()
{
    return ::get(getCharLambda);
}

Byte_order File_contents::get_BOM()
{
    return ::get_BOM(getCharLambda,false,oneByteBackLambda);
}

QString File_contents::get_iso8859_str()
{
    return ::get_iso8859_str(getCharLambda,false,oneByteBackLambda,data.size() - position);
}

QString File_contents::get_iso8859_str(const long long & len)
{
    return ::get_iso8859_str(getCharLambda,false,oneByteBackLambda,len);
}

QString File_contents::get_utf16_str(Byte_order bo)//не чекает BOM
{
    return ::get_utf16_str(getCharLambda,false,bo,oneByteBackLambda,data.size() - position);
}

QString File_contents::get_utf16_str(Byte_order bo, const long long & len)//не чекает BOM
{
    return ::get_utf16_str(getCharLambda,false,bo,oneByteBackLambda,len);
}

QString File_contents::get_utf8_str()
{
    return ::get_utf8_str(getCharLambda,false,oneByteBackLambda,data.size() - position);
}

QString File_contents::get_utf8_str(const long long & len)
{
    return ::get_utf8_str(getCharLambda,false,oneByteBackLambda,len);
}

QString File_contents::get_ucs2_str(Byte_order bo)//не чекает BOM
{
    return ::get_ucs2_str(getCharLambda,false,bo,oneByteBackLambda,data.size() - position);
}

QString File_contents::get_ucs2_str(Byte_order bo, const long long & len)//не чекает BOM
{
    return ::get_ucs2_str(getCharLambda,false,bo,oneByteBackLambda,len);
}

QByteArray File_contents::get_binary_till_end()
{
    QByteArray arr;
    while (!end())
        arr.append(ch());
    return arr;
}

QString File_contents::get_encoding_dependent_string(String_encoding enc, function<bool()> skip)//не чекает BOM
{
    return ::get_encoding_dependent_string(getCharLambda,false,oneByteBackLambda,data.size() - position,enc,skip);
}

QString File_contents::get_encoding_dependent_string(String_encoding enc, const long long & len, function<bool()> skip)//не чекает BOM
{
    return ::get_encoding_dependent_string(getCharLambda,false,oneByteBackLambda,len,enc,skip);
}

string File_contents::get_symbols(int amount)
{
    string str;
    for (int i = 0;i < amount;++i)
        str += ch();
    return str;
}

string File_contents::get_frame34_id()
{
    return get_symbols(4);
}
