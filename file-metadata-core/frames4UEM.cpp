#include "frame4.h"

//UFID
void Frames_4::UFID::extract() {
    QString url = getUrl();
    if (!url.isEmpty())
        file.getData().ufids[url] = getBinaryTillEnd();
}

/*
//ETCO
bool Frames_4::ETCO::parseData() {
    //
}

//EQU2
bool Frames_4::EQU2::parseData() {
    //
}

//USER
bool Frames_4::USER::parseData() {
    //
}

//USLT
bool Frames_4::USLT::parseData() {
    //
}

//MLLT
bool Frames_4::MLLT::parseData() {
    //
}

//MCDI
bool Frames_4::MCDI::parseData() {
    //
}
*/
