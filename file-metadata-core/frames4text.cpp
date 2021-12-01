#include "frame4.h"

void Frames_4::TIT2::extract() {
    setString(file.getData().generalInfo.title);
}

void Frames_4::TPE1::extract() {
    setString(file.getData().generalInfo.performer);
}

void Frames_4::TALB::extract() {
    setString(file.getData().generalInfo.album);
}

void Frames_4::TPE2::extract() {
    setTextField("Minor performer");
}

void Frames_4::TPE3::extract() {
    setTextField("Conductor");
}

void Frames_4::TPE4::extract() {
    setTextField("Modified by");
}

void Frames_4::TCON::extract() {
    setTextField("Content type");
}

void Frames_4::TDRC::extract() {
    setTextField("Recording time");
}
