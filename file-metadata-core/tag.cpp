#include "tag.h"
using namespace std;

Tag::Tag(Binary & file) :
    File_holder(file)
{}

Tag::~Tag() = default;

bool Tag::correct_char(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool Tag::correct_char(uchar c)
{
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
