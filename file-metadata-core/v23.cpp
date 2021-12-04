#include "v23.h"

Binary::V23::V23(Binary &f) :
    Tag34(f)
{}

Binary::V23::~V23() = default;

bool Binary::V23::parseHeader() {
    mByte flags = get();
    for (unsigned i = 0;i < 5;++i) {
        if (flags.test(i))
            return false;
    }

    unsynch = flags.test(7);
    bool extdh = flags.test(6);
    experimentalTag = flags.test(5);

    bool correctness = setLength([this] {
                                        return this->FileHolder::get();
                                    });
    endPosition = startPosition + 10 + length;
    if (correctness && extdh){
        correctness = parseExtendedHeader();
    }
    extremePositionOfFrame = endPosition - 11 - sizeOfPadding;
    return correctness;
}

bool Binary::V23::parseExtendedHeader() {
    for (int i = 0;i < 4;++i) {
        getb(sizeOfExtendedHeader);
    }

    expectedCrc.second = (getb(sizeOfExtendedHeader) > 127);//установлен первый бит первого флага
    getb(sizeOfExtendedHeader);//второй байт не имеет значимого контента

    for (int i = 3;i >= 0;--i) {
        sizeOfPadding += getb(sizeOfExtendedHeader)*Gl::power(256,i);
    }

    if (expectedCrc.second) {
        for (int i = 3;i >= 0;--i) {
            expectedCrc.first += getb(sizeOfExtendedHeader)*Gl::power(256,i);
        }
    }
    return true;
}

bool Binary::V23::isUserdefTxt(const char *const id) {
    return  (id[0] == 'T' && Binary::V23::correctId(id) && strcmp(id, "TALB") && strcmp(id, "TBPM")
     && strcmp(id, "TCOP") && strcmp(id, "TDAT") && strcmp(id, "TDLY") && strcmp(id, "TENC")
     && strcmp(id, "TEXT") && strcmp(id, "TFLT") && strcmp(id, "TIME") && strcmp(id, "TIT1")
     && strcmp(id, "TIT2") && strcmp(id, "TIT3") && strcmp(id, "TKEY") && strcmp(id, "TLAN")
     && strcmp(id, "TLEN") && strcmp(id, "TMED") && strcmp(id, "TOAL") && strcmp(id, "TOFN")
     && strcmp(id, "TOLY") && strcmp(id, "TOPE") && strcmp(id, "TORY") && strcmp(id, "TOWN")
     && strcmp(id, "TPE1") && strcmp(id, "TPE2") && strcmp(id, "TPE3") && strcmp(id, "TPE4")
     && strcmp(id, "TPOS") && strcmp(id, "TPUB") && strcmp(id, "TRCK") && strcmp(id, "TRDA")
     && strcmp(id, "TRSN") && strcmp(id, "TRSO") && strcmp(id, "TSIZ") && strcmp(id, "TSRC")
     && strcmp(id, "TSSE") && strcmp(id, "TYER")&& strcmp(id, "TCOM") && strcmp(id, "TCON"));
}

bool Binary::V23::handleCrc() {
    if (!content.setDataAndCheckSrc(file,unsynch,endPosition - sizeOfPadding - pos(),expectedCrc.first)) {
        qCritical() << "Frame3: посчитанный CRC32 не совпадает с переданным\n";
        return false;
    }
    else {
        extremePositionOfFrame = content.size() - 11 - sizeOfPadding;
        return true;
    }
}

void Binary::V23::actualParse() {
    while (pos() <= extremePositionOfFrame) {
        std::string frame_id = getFrameId();
        std::cout << "V2.3: got frame ID '" << frame_id.c_str() << "'\n\n";
        FrameParser frame(frame_id.c_str(), *this);
        if (frame.parse() == noId) {
            shift(-3);
        }
    }
}
