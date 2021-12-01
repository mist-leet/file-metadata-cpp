#include "frames4UEM.h"
using namespace std;

//ENCR
Binary::V24::ENCR::ENCR(Binary::V24 &t) :
    Frame4(t)
{}

Binary::V24::ENCR::~ENCR() = default;

bool Binary::V24::ENCR::parse_data()
{
    QString _url = get_url();
    uchar mark = get_group_mark();

    if (mark)
    {
        tag.encr_info().info[mark] = get_binary_till_end();
        tag.encr_info().url[mark] = _url;
    }
    else
        skip();

    return end();
}
