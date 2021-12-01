#include "frames3.h"
using namespace std;

//unknown
bool Binary::V23::UnknownFrame::parseHeader()
{
    int number_of_length_bytes = setLength([this](int &count)
                                            {
                                                return this->getb(count);
                                            }).first;//второй элемент пары всегда true
    int number_of_flag_bytes = 0;

    getb(number_of_flag_bytes);//первый байт с флагами
    getb(number_of_flag_bytes);//второй байт с флагами
    endPosition = startPosition + 4 + number_of_length_bytes + number_of_flag_bytes + length;
    return true;
}

bool Binary::V23::UnknownFrame::parseData()
{
    return skip();
}

//padding
bool Binary::V23::PaddingHandler::parseHeader()
{
    return true;
}

bool Binary::V23::PaddingHandler::parseData()
{
    seek(tag.endpos());
    return true;
}
