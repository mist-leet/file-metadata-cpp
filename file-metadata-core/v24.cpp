#include "v24.h"

Binary::V24::V24(Binary &f)
    : Tag34(f)
{}

Binary::V24::~V24() = default;

bool Binary::V24::parseHeader() {
    mByte flags = get();
    for (unsigned i = 0;i < 4;++i) {
        if (flags.test(i))//если установлены неопределённые флаги
            return false;
    }

    unsynch = flags.test(7);
    bool extdh = flags.test(6);
    experimentalTag = flags.test(5);
    footerPresence = flags.test(4);

    bool correctness = setLength([this] {
                                        return this->FileHolder::get();
                                    });
    if (footerPresence) {
        endPosition = startPosition + length + 20;
        extremePositionOfFrame = endPosition - 21;
    }
    else {
        endPosition = startPosition + length + 10;
        extremePositionOfFrame = endPosition - 11;
    }
    if (correctness && extdh) {
        correctness = parseExtendedHeader();
    }
    return correctness;
}

bool Binary::V24::parseExtendedHeader() {
    for (int i = 0;i < 4;++i)//длину тега можно узнать другим образом, поэтому байты длины можно игнорировать
        if (get(sizeOfExtendedHeader) > 127)
            return false;

    if (get(sizeOfExtendedHeader) != 1)//в стандарте определено только значение 1
        return false;

    mByte flags = get(sizeOfExtendedHeader);

    if (flags.test(6))
        if (get(sizeOfExtendedHeader) != 0)
            return false;

    expectedCrc.second = flags.test(5);
    if (expectedCrc.second)
        if (!setCrc())
            return (expectedCrc.second = false);

    restrictions.presence = flags.test(4);
    if (restrictions.presence)
        if (!setRestrictions())
            return (expectedCrc.second = restrictions.presence = false);

    return true;
}

bool Binary::V24::setCrc() {
    if (get(sizeOfExtendedHeader) != 5)
        return false;

    expectedCrc.second = true;

    unsigned char buf[5];

    if ((buf[4] = get(sizeOfExtendedHeader)) > 15)
        expectedCrc.second = false;

    for (int i = 3;i >= 0;--i)
        if ((buf[i] = get(sizeOfExtendedHeader)) > 127)
            expectedCrc.second = false;

    if (expectedCrc.second)
        for (int i = 4;i >= 0;--i)
            expectedCrc.first += buf[i]*static_cast<unsigned long>(Gl::power(128,i));

    return true;
}

bool Binary::V24::setRestrictions() {
    if (get(sizeOfExtendedHeader) != 1)
        return false;
    else
        restrictions.presence = true;

    mByte r = getb(sizeOfExtendedHeader);

    //ограничения размера и количества фреймов
    if (r.test(7))
    {
        restrictions.maxFrames = 32;
        if (r.test(6))
            {restrictions.maxSize = Gl::kbyte(4);}
        else
            {restrictions.maxSize = Gl::kbyte(40);}
    }
    else
    {
        if (r.test(6))
        {
            restrictions.maxFrames = 64;
            restrictions.maxSize = Gl::kbyte(128);
        }
        if (!r.test(6))
        {
            restrictions.maxFrames = 128;
            restrictions.maxSize = Gl::mbyte();
        }
    }
    //ограничения по кодировке текста
    restrictions.encodingRest = r.test(5);
    //ограничения по количеству символов в одном фрейме
    if (r.test(4))
    {
        if (r.test(3))
            restrictions.maxCharPerFrame = 30;
        else
            restrictions.maxCharPerFrame = 128;
    }
    else //по дефолту стоит максимально возможный размер
        if (r.test(3))
            restrictions.maxCharPerFrame = 1024;
    //ограничения по кодировке изображений
    restrictions.imageEncodingRest = r.test(2);
    //ограничения по размеру изображений
    restrictions.imageSizeRest = std::make_pair(r.test(1),r.test(0));

    return true;
}

bool Binary::V24::isUserdefTxt(const char *const id) {
    return  (id[0] == 'T' && Binary::V24::correctId(id) && strcmp(id, "TIT1") && strcmp(id, "TIT2") && strcmp(id, "TIT3")
            && strcmp(id, "TALB") && strcmp(id, "TOAL")
     && strcmp(id, "TRCK") && strcmp(id, "TPOS") && strcmp(id, "TSST") && strcmp(id, "TSRC") && strcmp(id, "TPE1")
     && strcmp(id, "TPE2") && strcmp(id, "TPE3") && strcmp(id, "TPE4") && strcmp(id, "TOPE") && strcmp(id, "TEXT")
     && strcmp(id, "TOLY") && strcmp(id, "TCOM") && strcmp(id, "TMCL") && strcmp(id, "TIPL") && strcmp(id, "TENC")
     && strcmp(id, "TBPM") && strcmp(id, "TLEN") && strcmp(id, "TKEY") && strcmp(id, "TLAN") && strcmp(id, "TCON")
     && strcmp(id, "TFLT") && strcmp(id, "TMED") && strcmp(id, "TMOO") && strcmp(id, "TCOP") && strcmp(id, "TPRO")
     && strcmp(id, "TPUB") && strcmp(id, "TOWN") && strcmp(id, "TRSN") && strcmp(id, "TRSO") && strcmp(id, "TOFN")
     && strcmp(id, "TDLY") && strcmp(id, "TDEN") && strcmp(id, "TDOR") && strcmp(id, "TDRC") && strcmp(id, "TDRL")
     && strcmp(id, "TDTG") && strcmp(id, "TSSE") && strcmp(id, "TSOA") && strcmp(id, "TSOP") && strcmp(id, "TSOT"));
}

bool Binary::V24::handleCrc() {
    ulong data_len = endPosition - pos();
    if (footerPresence)
        data_len -= 10;

    if (!content.setDataAndCheckSrc(file, unsynch, data_len, expectedCrc.first)) {
        qCritical() << "посчитанный CRC32 не совпадает с переданным\n";
        return false;
    }
    else {
        extremePositionOfFrame = content.size() - 11;
        return true;
    }
}

void Binary::V24::actualParse() {
    while (pos() <= extremePositionOfFrame) {
        std::string frame_id = getFrameId();
        FrameParser frame(frame_id.c_str(), *this);
        if (frame.parse() == noId)
            shift(-3);
    }
}
