#include "frames4SA.h"
using namespace std;

//SIGN
bool Binary::V24::SIGN::parseData()
{
    uchar mark = getGroupMark();

    if (Frame4::isGroupOrEncrMark(mark))
        tag.groupInfo().sign[mark] = getBinaryTillEnd();

    return skip();
}
