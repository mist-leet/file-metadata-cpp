#include "frame3.h"

//unknown
bool Frames_3::UnknownFrame::parseHeader() {
    ulong number_of_length_bytes = setLength([this](ulong &count) {
                                                return this->getb(count);
                                            });
    ulong number_of_flag_bytes = 0;

    getb(number_of_flag_bytes);//первый байт с флагами
    getb(number_of_flag_bytes);//второй байт с флагами
    endPosition = startPosition + 4 + number_of_length_bytes + number_of_flag_bytes + length;
    return true;
}

//padding
bool Frames_3::PaddingHandler::parseHeader() {
    return true;
}
bool Frames_3::PaddingHandler::parseData() {
    seek(tag.endpos());
    return true;
}

//title (TIT2)
void Frames_3::TIT2::extract() {
    qDebug() << "Frame3, TIT2: starting to parse data\n";
    setString(file.getData().generalInfo.title);
    qDebug() << "Frame3, TIT2: parsing ended\n";
}

void Frames_3::TPE1::extract() {
    qDebug() << "Frame3, TPE1: starting to parse data\n";
    setString(file.getData().generalInfo.performer);
    qDebug() << "Frame3, TPE1: parsing ended\n";
}

void Frames_3::TALB::extract() {
    qDebug() << "Frame3, TALB: starting to parse data\n";
    setString(file.getData().generalInfo.album);
    qDebug() << "Frame3, TALB: parsing ended\n";
}

void Frames_3::TPE2::extract() {
    qDebug() << "Frame3, TPE2: starting to parse data\n";
    setTextField("Minor performer");
    qDebug() << "Frame3, TPE2: parsing ended\n";
}

void Frames_3::TPE3::extract() {
    qDebug() << "Frame3, TPE3: starting to parse data\n";
    setTextField("Conductor");
    qDebug() << "Frame3, TPE3: parsing ended\n";
}

void Frames_3::TPE4::extract() {
    qDebug() << "Frame3, TPE4: starting to parse data\n";
    setTextField("Modified by");
    qDebug() << "Frame3, TPE4: parsing ended\n";
}

void Frames_3::TCON::extract() {
    setTextField("Content type");
}

void Frames_3::TYER::extract() {
    setTextField("Recording time");
}
