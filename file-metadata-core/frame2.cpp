#include "frame2.h"
using namespace std;

Frame2::Frame2(Binary::V22 &t)
    : Frame(t)
    , tag(t)
{
    start_position = pos() - 3;
    end_position = start_position + 3;
}

Frame2::~Frame2() = default;

bool Frame2::parse()
{
    parse_header();
    return parse_data();
}

bool Frame2::parse_header()
{
    end_position = start_position + 3 + set_length([this](int &count)
                                                        {
                                                            return this->getb(count);
                                                        }).first
                                                        + length;//set_length возвращает кол-во байт, ушедшее на запись длины
    return true;
}

bool Frame2::set_string_encoding()
{
    unsigned char enc_byte = getb();
    switch (enc_byte)
    {
    case 0:
        encoding = iso_8859_1;
        return true;

    case 1:
        encoding = ucs_2be;
        return true;

    default:
        encoding = not_given;
        return false;
    }
}
