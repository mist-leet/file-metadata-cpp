#include "frames4.h"
using namespace std;

bool Binary::V24::unknown_frame::parse_frame_data()
{
    seek(pos() + data_length);
    return true;
}

bool Binary::V24::SIGN_4::parse_frame_data()
{
    unsigned char mark = getb();
    QByteArray arr;
    while (*this)
    {
        arr.append(_ch());
    }

    grouping_info.sign[mark] = arr;

    return pos() == end_position;
}

bool Binary::V24::GRID_4::parse_frame_data()
{
    string url = "";
    do
    {
        url += _ch();
    } while (*this && url[url.size() - 1]);
    //дописать
}

/*
bool Binary::V24::ENCR_4::parse_frame_data()
{
    //парсить
}
*/
