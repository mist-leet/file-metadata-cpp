#include "frame2.h"
using namespace std;

bool Binary::V22::Frame2::parse_frame_header()
{
    int size_of_data = 0;
    for (int i = 2;i >= 0;--i)
        length += static_cast<unsigned long>(getb(size_of_data))*power(256,i);
    end_position = start_position + 3 + size_of_data + length;
    return true;//ошибок при парсинге возникнуть не может
}

bool Binary::V22::Frame2::parse_frame()
{
    parse_frame_header();
    return parse_frame_data();
}
