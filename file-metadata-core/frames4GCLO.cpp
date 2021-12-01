#include "frames4GCLO.h"
using namespace std;

//GRID
bool Binary::V24::GRID::parseData()
{
    QString u = getUrl();
    uchar mark = getGroupMark();

    if (Frame4::isGroupOrEncrMark(mark))
    {
        tag.groupInfo().info[mark] = getBinaryTillEnd();
        tag.groupInfo().url[mark] = u;
    }

    return skip();
}
