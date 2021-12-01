#include "frame.h"
using namespace std;

Frame::Frame(Tag &t)
    : File_holder(t.get_file(), t.get_unsynch())
{}

Frame::~Frame() = default;

QString Frame::get_url() const
{
    return get_iso8859_str();
}

QString Frame::get_url(const long long & dur) const
{
    return get_iso8859_str(dur);
}
