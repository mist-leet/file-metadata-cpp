#include "tag.h"
using namespace std;

Tag::Tag(Binary &file) :
    FileHolder(file)
{}

Tag::~Tag() = default;

bool Tag::correctChar(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool Tag::correctChar(uchar c)
{
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
