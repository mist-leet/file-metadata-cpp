#include "frame4.h"

Frame4::Frame4(Binary::V24 &t)
    : Frame34(t.getFile(), t.getUnsynch())
    , tag(t)
{
    synchsafeHeader = true;
    if (tag.hasPreextractedData()) {
        startPosition = tag.getContent().pos() - 4;
        endPosition = startPosition + 4;
    }
}

Frame4::~Frame4() = default;

bool Frame4::parseHeader() {
    qDebug() << "Frame4: starting to parse header\n";
    if (!setLength([this] {
                        return this->get();
                         })) {
        qDebug() << "Frame4: failed to parse header because of failing to set length\n";
        return false;
    }

    dataLength = length;
    endPosition = startPosition + 10 + length;

    mByte status = getb();//неопределённые флаги могут быть выставлены, это не ошибка

    frameStatus.tagAlterPreservation = !status.test(6);
    frameStatus.fileAlterPreservation = !status.test(5);
    frameStatus.readOnly = status.test(4);

    mByte format = get();//неопределённые флаги не должны быть выставлены
    if (format.test(7) || format.test(5) || format.test(4)) {
        qDebug() << "Frame4: failed to parse header because of undefined flags being set\n";
        return false;
    }

    ulong extra_data_size = 0;

    if (format.test(6))//group ID вообще не интересует
        get();

    bool compressionPresence = format.test(3);
    bool uncompressedSizePresence = format.test(0);
    if (compressionPresence && !uncompressedSizePresence) {
        qDebug() << "Frame4: failed to parse header: can't uncompress frame\n";
        return false;
    }

    bool encryption = format.test(2);
    if (encryption) {
        qDebug() << "Frame4: frame is encrypted and thus unreadable\n";
        get();
        unreadable = true;
    }

    unsynch = format.test(1);

    if (compressionPresence || uncompressedSizePresence) {
        bool correct = true;
        unsigned char buf[4];
        for (int i = 3;i >= 0;--i) {
            buf[i] = get(extra_data_size);
            if (buf[i]  > 127)
                correct = false;//raw data size хранится в synchsafe int
        }

        if (correct)
            for (int i = 3;i >= 0;--i)
                uncompressedSize += static_cast<unsigned long>(buf[i])*Gl::power(128,i);
    }

    dataLength -= extra_data_size;

    qDebug() << "Frame4: successfully parsed header, length is" << length << endl;
    return true;
}

bool Frame4::tagHasContent() const {
    return tag.hasPreextractedData();
}

FileContents & Frame4::tagsContent() const {
    return tag.getContent();
}

QString Frame4::getEncodingDependentStringFromContents(FileContents &c) const {
    return c.getEncodingDependentString(four);
}

QString Frame4::getEncodingDependentStringFromContents(FileContents &c, ulong len) const {
    return c.getEncodingDependentString(four, len);
}

QString Frame4::getEncodingDependentStringFileHolder() const {
    return FileHolder::getEncodingDependentString(four);
}

QString Frame4::getEncodingDependentStringFileHolder(ulong len) const {
    return FileHolder::getEncodingDependentString(four, len);
}

QList<QString> Frame4::__getList(ulong len, QChar separator) const {
    return FileHolder::getList(len, four, separator);
}

QList<QString> Frame4::__getList(FileContents &fc, ulong len, QChar separator) const {
    return fc.getList(len, four, separator);
}
