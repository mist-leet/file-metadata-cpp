#include "frames4unknown.h"
using namespace std;

//unknown
bool Binary::V24::UnknownFrame::parseHeader()
{
    if (!setLength([this](int &count)
                    {
                        return this->getb(count);
                    }).second)
        return false;
    else
    {
        endPosition = startPosition + 10 + length;//в 4 версии гарантируется, что хедер занимает 10 байт
        return true;
    }
}

bool Binary::V24::UnknownFrame::parseData()
{
    return skip();
}

//padding
bool Binary::V24::PaddingHandler::parseHeader()
{
    return true;
}

bool Binary::V24::PaddingHandler::parseData()
{
    seek(tag.endpos());
    return true;
}
