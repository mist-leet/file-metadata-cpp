#include "file-holder.h"
using namespace std;

unsigned char File_holder::get() const
{
    return file.get();
}

unsigned char File_holder::getb() const
{
    return file.getb(unsynch);
}

char File_holder::ch() const
{
    return file.ch();
}

char File_holder::_ch() const
{
    return file._ch(unsynch);
}

long File_holder::get_utf8() const
{
    return file.get_utf8(unsynch);
}

long File_holder::get_utf16(bool big_endian)  const
{
    return file.get_utf16(unsynch,big_endian);
}

long File_holder::get_usc2(bool big_endian) const
{
    return file.get_usc2(unsynch,big_endian);
}

bool File_holder::seek(long long position) const
{
    return file.seek(position);
}

long long File_holder::pos() const
{
    return file.pos();
}

void File_holder::skip() const
{
    file.seek(end_position);
}

File_holder::operator bool() const
{
    return file.pos() < end_position;
}

File_holder::File_holder(Binary & file_) :
    file(file_),
    unsynch(false),
    length(0),
    start_position(pos() - 5),
    end_position(pos() + 1)
    {}

File_holder::File_holder(Binary & file_, bool unsynch_) :
    file(file_),
    unsynch(unsynch_),
    length(0),
    start_position(pos() - 3),
    end_position(pos() + 1)
    {}
