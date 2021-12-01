#include "tag34.h"
using namespace std;

Tag34::Tag34(Binary &f)
    : Tag(f)
{}

Tag34::~Tag34() = default;

Encryption_method_markers & Tag34::encr_info()
{
    return encryption_info;
}

Group_markers & Tag34::group_info()
{
    return grouping_info;
}

string Tag34::get_frame_id()
{
    if (content)
        return content.get_frame34_id();
    else
        return File_holder::get_symbols(4);
}

long long Tag34::pos() const
{
    if (content)
        return content.pos();
    else
        return File_holder::pos();
}

void Tag34::shift(long long offset) const
{
    if (content)
        content.shift(offset);
    else
        File_holder::shift(offset);
}

bool Tag34::correct_id(const char * const id)
{
    for (int i = 0;i < 4;++i)
        if (!correct_char(id[i]))
            return false;
    return !id[4];
}

bool Tag34::is_userdef_url(const char * const id)
{
    return (id[0] == 'W' && Tag34::correct_id(id) && strcmp(id, "WCOM") && strcmp(id, "WCOP") && strcmp(id, "WOAF") &&
        strcmp(id, "WOAR") && strcmp(id, "WOAS") && strcmp(id, "WORS") && strcmp(id, "WPAY") && strcmp(id, "WPUB"));
}

bool Tag34::is_free_frame(const char * const id)
{
    return (id[0] == 'X' || id[0] == 'Y' || id[0] == 'Z') && Tag34::correct_id(id);
}

bool Tag34::has_preextracted_data() const
{
    return content;
}

File_contents & Tag34::get_content()
{
    return content;
}
