#include "frames4sa.h"
using namespace std;

//SIGN
Binary::V24::SIGN::SIGN(Binary::V24 &t) :
    Frame4(t)
{}

Binary::V24::SIGN::~SIGN() = default;

bool Binary::V24::SIGN::parse_data()
{
    uchar mark = get_group_mark();

    if (mark)
        tag.group_info().sign[mark] = get_binary_till_end();
    else
        skip();

    return end();
}
