#include "frame3.h"

Frame3::Frame3(Binary::V23 &t)
    : Frame34(t.getFile(), t.getUnsynch())
    , tag(t)
{
    if (tag.hasPreextractedData()) {
        startPosition = tag.getContent().pos() - 4;
        endPosition = startPosition + 4;
    }
}

Frame3::~Frame3() = default;

bool Frame3::parseHeader() {
    qDebug() << "Frame3: starting to parse header\n";
    ulong number_of_length_bytes = setLength([this](ulong &count) {
                                                return this->getb(count);
                                            });
    qDebug() << "Frame3: length is set, length =" << length << endl;
    ulong extra_data_size = 0, number_of_flag_bytes = 0;

    dataLength = length;

    mByte status = getb(number_of_flag_bytes);
    frameStatus.tagAlterPreservation = !status.test(7);
    frameStatus.fileAlterPreservation = !status.test(6);
    frameStatus.readOnly = status.test(5);

    mByte format = getb(number_of_flag_bytes);

    endPosition = startPosition + 4 + number_of_length_bytes + number_of_flag_bytes + length;

    for (unsigned i = 0;i < 4;++i)
        if (format.test(i)) {
            qDebug() << "Frame3: failed to parse header because of undefined flags being set\n";
            return false;
        }

    if (format.test(7))
        for (int i = 3;i >= 0;--i)
            uncompressedSize += static_cast<unsigned long>(getb(extra_data_size))*Gl::power(256,i);

    frameFormat.encryption = format.test(6);
    if (frameFormat.encryption)
    {
        uchar mark = getb(extra_data_size);
        if (Frame3::is_group_or_encr_mark(mark))
        {
            frame_format.encryption_method_marker = mark;
            frame_format.encryption = true;
        }
    }

    frameFormat.groupIdPresence = format.test(5);
    if (frameFormat.groupIdPresence)
    {
        uchar mark = getb(extra_data_size);
        if (Frame3::is_group_or_encr_mark(mark))
        {
            frame_format.group_id = mark;
            frame_format.group_id_presence = true;
        }
    }

    dataLength -= extra_data_size;

    qDebug() << "Frame3: header is successfully parsed, length is" << length << endl;
    return true;
}

bool Frame3::tagHasContent() const {
    return tag.hasPreextractedData();
}

FileContents & Frame3::tagsContent() const {
    return tag.getContent();
}

QString Frame3::getEncodingDependentStringFromContents(FileContents &c) const {
    return c.getEncodingDependentString(three);
}

QString Frame3::getEncodingDependentStringFromContents(FileContents &c, ulong len) const {
    return c.getEncodingDependentString(three, len);
}

QString Frame3::getEncodingDependentStringFileHolder() const {
    return FileHolder::getEncodingDependentString(three);
}

QString Frame3::getEncodingDependentStringFileHolder(ulong len) const {
    return FileHolder::getEncodingDependentString(three, len);
}

QList<QString> Frame3::__getList(ulong len, QChar separator) const {
    return FileHolder::getList(len, three, separator);
}

QList<QString> Frame3::__getList(FileContents &fc, ulong len, QChar separator) const {
    return fc.getList(len, three, separator);
}
