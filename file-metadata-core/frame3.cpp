#include "frame3.h"
using namespace std;

Frame3::Frame3(Binary::V23 &t)
    : Frame34(t)
    , tag(t)
{
    if (tag.hasPreextractedData())
    {
        startPosition = tag.getContent().pos() - 4;
        endPosition = startPosition + 4;
    }
}

Frame3::~Frame3() = default;

bool Frame3::parseHeader()
{
    int number_of_length_bytes = setLength([this](int &count)
                                            {
                                                return this->getb(count);
                                            }).first;
    int extra_data_size = 0, number_of_flag_bytes = 0;

    dataLength = length;

    mByte status = getb(number_of_flag_bytes);
    frameStatus.tagAlterPreservation = !status.test(7);
    frameStatus.fileAlterPreservation = !status.test(6);
    frameStatus.readOnly = status.test(5);

    mByte format = getb(number_of_flag_bytes);

    endPosition = startPosition + 4 + number_of_length_bytes + number_of_flag_bytes + length;

    for (unsigned i = 0;i < 4;++i)
        if (format.test(i))
            return false;

    frameFormat.compressionInfo.second = format.test(7);
    if (frameFormat.compressionInfo.second)
        for (int i = 3;i >= 0;--i)
            frameFormat.compressionInfo.first += static_cast<unsigned long>(getb(extra_data_size))*power(256,i);

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

    return true;
}

bool Frame3::isGroupOrEncrMark(uchar mark)
{
    return mark >= 128;
}

uchar Frame3::getGroupMark() const
{
    uchar mark = getb();
    if (Frame3::isGroupOrEncrMark(mark))
        return mark;
    else
        return 0;
}

bool Frame3::tagHasContent() const
{
    return tag.hasPreextractedData();
}

FileContents & Frame3::tagsContent() const
{
    return tag.getContent();
}

QString Frame3::getEncodingDependentString(FileContents &c) const
{
    return c.getEncodingDependentString(three);
}

QString Frame3::getEncodingDependentString(FileContents &c, const long long &dur) const
{
    return c.getEncodingDependentString(three, dur);
}

QString Frame3::getEncodingDependentString(bool) const//фиктивный аргумент
{
    return FileHolder::getEncodingDependentString(three);
}

QString Frame3::getEncodingDependentString(bool, const long long &dur) const//фиктивный аргумент
{
    return FileHolder::getEncodingDependentString(three, dur);
}
