#include "frame.h"

void Frame::extract() {
    //does nothing by default
}

bool Frame::parseData() {
    extract();
    return skip();
}

void Frame::setTextField(QString id) const {
    QString s = getEncodingDependentString();
    if (!s.isEmpty())
        file.getData().textFields[id] = s;
}

void Frame::setString(QString &s) const {
    QString info = getEncodingDependentString();
    if (!info.isEmpty())
        s = info;
}

Frame::Frame(Binary &f, bool u)
    : FileHolder(f, u)
{}

Frame::~Frame() = default;
