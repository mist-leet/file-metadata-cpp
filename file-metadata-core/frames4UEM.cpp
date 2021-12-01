#include "frames4UEM.h"
using namespace std;

//ENCR
bool Binary::V24::ENCR::parseData()
{
    QString _url = getUrl();
    uchar mark = getGroupMark();

    if (Frame4::isGroupOrEncrMark(mark))
    {
        tag.encrInfo().info[mark] = getBinaryTillEnd();
        tag.encrInfo().url[mark] = _url;
    }

    return skip();
}

//ETCO
bool Binary::V24::ETCO::parseData()
{
    //
}

//EQU2
bool Binary::V24::EQU2::parseData()
{
    //
}

//UFID
bool Binary::V24::UFID::parseData()
{
    QString url = getUrl();
    file.getData().ufids[url] = getBinaryTillEnd();
    return skip();
}

//USER
bool Binary::V24::USER::parseData()
{
    //
}

//USLT
bool Binary::V24::USLT::parseData()
{
    //
}

//MLLT
bool Binary::V24::MLLT::parseData()
{
    //
}

//MCDI
bool Binary::V24::MCDI::parseData()
{
    //
}
