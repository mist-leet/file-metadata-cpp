#include "frames4unknown.h"
using namespace std;

//unknown
Binary::V24::unknown_frame::unknown_frame(Binary::V24 &t)
    : Frame4(t)
{}

Binary::V24::unknown_frame::~unknown_frame() = default;

bool Binary::V24::unknown_frame::parse_header()
{
    if (!set_length([this](int &count)
                    {
                        return this->getb(count);
                    }).second)
        return false;
    else
    {
        end_position = start_position + 10 + length;//в 4 версии гарантируется, что хедер занимает 10 байт
        return true;
    }
}

bool Binary::V24::unknown_frame::parse_data()
{
    return skip();
}

//padding
Binary::V24::padding_handler::padding_handler(Binary::V24 &t)
    : Frame4(t)
{}

Binary::V24::padding_handler::~padding_handler() = default;

bool Binary::V24::padding_handler::parse_header()
{
    return true;
}

bool Binary::V24::padding_handler::parse_data()
{
    seek(tag.endpos());
    return true;
}
