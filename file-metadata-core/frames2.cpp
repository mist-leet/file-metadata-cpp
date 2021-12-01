#include "frame2.h"

void Frames_2::TT2::extract() {
    setString(file.getData().generalInfo.title);
}

void Frames_2::TP1::extract() {
    setString(file.getData().generalInfo.performer);
}

void Frames_2::TAL::extract() {
    setString(file.getData().generalInfo.album);
}

void Frames_2::TP2::extract() {
    setTextField("Minor performer");
}

void Frames_2::TP3::extract() {
    setTextField("Conductor");
}

void Frames_2::TP4::extract() {
    setTextField("Modified by");
}

void Frames_2::TCO::extract() {
    setTextField("Content type");
}

void Frames_2::TYE::extract() {
    setTextField("Recording time");
}
