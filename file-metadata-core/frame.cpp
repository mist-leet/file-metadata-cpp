#include "frame.h"
using namespace std;

Frame::Frame(Tag &t)
    : FileHolder(t.getFile(), t.getUnsynch())
{}

Frame::~Frame() = default;

QString Frame::getUrl() const
{
    return getIso8859Str();
}

QString Frame::getUrl(const long long &dur) const
{
    return getIso8859Str(dur);
}
