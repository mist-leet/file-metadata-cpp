#include "frame4.h"

//unknown
bool Frames_4::UnknownFrame::parseHeader() {
    qDebug() << "Frame4: started to parse header\n";
    if (!setLength([this] {
                        return this->getb();
                    }))
        return false;
    else {
        endPosition = startPosition + 10 + length;//в 4 версии гарантируется, что хедер занимает 10 байт
        qDebug() << "Frame4: header parsed successfully, length is" << length << endl;
        return true;
    }
}

//padding
bool Frames_4::PaddingHandler::parseHeader() {
    qDebug() << "Frame4: padding found\n";
    return true;
}
bool Frames_4::PaddingHandler::parseData() {
    seek(tag.endpos());
    return true;
}
