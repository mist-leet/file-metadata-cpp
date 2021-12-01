#include "frame2.h"
using namespace std;

Frame2::Frame2(Binary::V22 &t)
    : Frame(t)
    , tag(t)
{
    startPosition = pos() - 3;
    endPosition = startPosition + 3;
}

Frame2::~Frame2() = default;

bool Frame2::parse()
{
    parseHeader();
    return parseData();
}

bool Frame2::parseHeader()
{
    endPosition = startPosition + 3 + setLength([this](int &count)
                                                        {
                                                            return this->getb(count);
                                                        }).first
                                                        + length;//set_length возвращает кол-во байт, ушедшее на запись длины
    return true;
}

QString Frame2::getEncodingDependentString() const
{
    return FileHolder::getEncodingDependentString(two);
}

QString Frame2::getEncodingDependentString(const long long &dur) const
{
    return FileHolder::getEncodingDependentString(two, dur);
}
