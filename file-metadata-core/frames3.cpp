#include "frames3.h"
using namespace std;

//unknown
Binary::V23::unknown_frame::unknown_frame(Binary::V23 &t)
    : Frame3(t)
{}

Binary::V23::unknown_frame::~unknown_frame() = default;

bool Binary::V23::unknown_frame::parse_data()
{
    return skip();
}

bool Binary::V23::unknown_frame::parse_header()
{
    int number_of_length_bytes = set_length([this](int &count)
                                            {
                                                return this->getb(count);
                                            }).first//второй элемент пары всегда true
            , number_of_flag_bytes = 0;

    getb(number_of_flag_bytes);//первый байт с флагами
    getb(number_of_flag_bytes);//второй байт с флагами
    end_position = start_position + 4 + number_of_length_bytes + number_of_flag_bytes + length;
    return true;
}

//padding
Binary::V23::padding_handler::padding_handler(Binary::V23 &t)
    : Frame3(t)
{}

Binary::V23::padding_handler::~padding_handler() = default;

bool Binary::V23::padding_handler::parse_header()
{
    return true;
}

bool Binary::V23::padding_handler::parse_data()
{
    seek(tag.endpos());
    return true;
}
