#include "frames4gclo.h"
using namespace std;

//GRID
Binary::V24::GRID::GRID(Binary::V24 &t) :
    Frame4(t)
{}

Binary::V24::GRID::~GRID() = default;

bool Binary::V24::GRID::parse_data()
{
    QString _url = get_url();
    uchar mark = get_group_mark();

    if (mark)
    {
        tag.group_info().info[mark] = get_binary_till_end();
        tag.group_info().url[mark] = _url;
    }
    else
        skip();

    return end();
}
