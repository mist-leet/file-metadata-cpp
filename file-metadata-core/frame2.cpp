#include "frame2.h"

Frame2::Frame2(Binary::V22 &t)
    : Frame(t.getFile(), t.getUnsynch())
{
    startPosition = pos() - 3;
    endPosition = startPosition + 3;
}

Frame2::~Frame2() = default;

bool Frame2::parse() {
    qDebug() << "Frame2: starting to parse" << endl;
    parseHeader();
    return parseData();
}

bool Frame2::parseHeader() {
    qDebug() << "Frame2: starting to parse header" << endl;
    endPosition = startPosition + 3 + setLength([this](ulong &count) {
                                                            return this->getb(count);
                                                        })
                                                        + length;//setLength.first содержит кол-во байт, ушедшее на запись длины
    qDebug() << "Frame2: header parsed\n";
    return true;
}

QString Frame2::getEncodingDependentString() const {
    qDebug() << "Frame2: getting encoding dependent for V 2 string till end\n";
    return FileHolder::getEncodingDependentString(two);
}

QString Frame2::getEncodingDependentString(ulong len) const {
    qDebug() << "Frame2: getting encoding dependent for V 2 string with length" << len << endl;
    return FileHolder::getEncodingDependentString(two, len);
}

QList<QString> Frame2::getList(ulong len, QChar separator) const {
    qDebug() << "Frame2: getting list for V 2 with length" << len << "and deliminator" << separator << endl;
    return FileHolder::getList(len, two, separator);
}
