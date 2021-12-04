#include "v22.h"

Binary::V22::V22(Binary &f) :
    Tag(f)
{}

Binary::V22::~V22() = default;

bool Binary::V22::parseHeader() {
    mByte flags = get();
    unsynch = flags.test(7);
    bool correctness = setLength([this] {
                                        return this->FileHolder::get();
                                    });
    endPosition = startPosition + 10 + length;
    extremePositionOfFrame = endPosition - 7;
    if (correctness) {
        correctness = !flags.test(6);
    }
    return correctness;
}

std::string Binary::V22::getFrameId() {
    return getSymbols(3);
}

bool Binary::V22::correctId(const char *const id) {
    for (int i = 0;i < 3;++i)
        if (!correctChar(id[i]))
            return false;
    return !id[3];
}

bool Binary::V22::isUserdefTxt(const char *const id) {
    return (id[0] == 'T' && V22::correctId(id) && strcmp(id, "TAL") && strcmp(id, "TBP") && strcmp(id, "TCM")
     && strcmp(id, "TCR") && strcmp(id, "TDA") && strcmp(id, "TDY") && strcmp(id, "TEN")
     && strcmp(id, "TFT") && strcmp(id, "TIM") && strcmp(id, "TKE") && strcmp(id, "TLA")
     && strcmp(id, "TLE") && strcmp(id, "TMT") && strcmp(id, "TOA") && strcmp(id, "TOF")
     && strcmp(id, "TOL") && strcmp(id, "TOR") && strcmp(id, "TOT") && strcmp(id, "TP1")
     && strcmp(id, "TP2") && strcmp(id, "TP3") && strcmp(id, "TP4") && strcmp(id, "TPA")
     && strcmp(id, "TPB") && strcmp(id, "TRC") && strcmp(id, "TRD") && strcmp(id, "TRK")
     && strcmp(id, "TSI") && strcmp(id, "TSS") && strcmp(id, "TT1") && strcmp(id, "TT2")
     && strcmp(id, "TT3") && strcmp(id, "TXT") && strcmp(id, "TYE") && strcmp(id, "TCO"));
}

bool Binary::V22::isUserdefUrl(const char *const id) {
    return (id[0] == 'W' && V22::correctId(id) && strcmp(id, "WAF") && strcmp(id, "WAR") && strcmp(id, "WAS")
             && strcmp(id, "WCM") && strcmp(id, "WCP") && strcmp(id, "WPB"));
}

bool Binary::V22::isFreeFrame(const char * const id) {
    return (id[0] == 'X' || id[0] == 'Y' || id[0] == 'Z') && V22::correctId(id);
}

bool Binary::V22::parseData() {
    while (pos() <= extremePositionOfFrame) {
        std::string frame_id = getFrameId();
        FrameParser frame(frame_id.c_str(), *this);
        if (frame.parse() == noId)
            shift(-2);
    }
    if (!end()){
        skip();
    }
    return true;
}
