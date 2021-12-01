#include "frame4.h"
using namespace std;

Frame4::Frame4(Binary::V24 &t)
    : Frame34(t)
    , tag(t)
{
    synchsafeHeader = true;
    if (tag.hasPreextractedData())
    {
        startPosition = tag.getContent().pos() - 4;
        endPosition = startPosition + 4;
    }
}

Frame4::~Frame4() = default;

bool Frame4::isGroupOrEncrMark(uchar c)
{
    return c >= 128 && c <= 240;
}

uchar Frame4::getGroupMark() const
{
    uchar mark = getb();
    if (Frame4::isGroupOrEncrMark(mark))
        return mark;
    else
        return 0;
}

bool Frame4::parseHeader()
{//функция начинает работу после frame ID
    if (!setLength([this](int &count)
                    {
                        return this->get(count);
                    }).second)
        return false;

    dataLength = length;

    endPosition = startPosition + 10 + length;

    mByte status = getb();//неопределённые флаги могут быть выставлены, это не ошибка

    frameStatus.tagAlterPreservation = !status.test(6);
    frameStatus.fileAlterPreservation = !status.test(5);
    frameStatus.readOnly = status.test(4);

    mByte format = get();//неопределённые флаги не должны быть выставлены
    if (format.test(7) || format.test(5) || format.test(4))
        return false;

    int extra_data_size = 0;

    frameFormat.groupIdPresence = format.test(6);
    if (frameFormat.groupIdPresence)
    {
        uchar mark = get(extra_data_size);
        if (Frame4::isGroupOrEncrMark(mark))
            frameFormat.groupId = mark;
        else
            frameFormat.groupIdPresence = false;
    }

    if (format.test(3))
    {
        if (format.test(0))
            frameFormat.compressionInfo.second = true;
        else
            return false;
    }

    frameFormat.encryption = format.test(2);
    if (frameFormat.encryption)
    {
        uchar mark = get(extra_data_size);
        if (Frame4::isGroupOrEncrMark(mark))
            frameFormat.encryptionMethodMarker = mark;
        else
            frameFormat.encryption = false;
    }

    unsynch = format.test(1);

    if (frameFormat.compressionInfo.second || format.test(0))
    {
        bool correct = true;
        unsigned char buf[4];
        for (int i = 3;i >= 0;--i)
        {
            buf[i] = get(extra_data_size);
            if (buf[i]  > 127)
                correct = false;//raw data size хранится в synchsafe int
        }

        if (correct)
            for (int i = 3;i >= 0;--i)
                frameFormat.compressionInfo.first += static_cast<unsigned long>(buf[i])*power(128,i);
    }

    dataLength -= extra_data_size;

    return true;
}

bool Frame4::tagHasContent() const
{
    return tag.hasPreextractedData();
}

FileContents & Frame4::tagsContent() const
{
    return tag.getContent();
}

QString Frame4::getEncodingDependentString(FileContents &c) const
{
    return c.getEncodingDependentString(four);
}

QString Frame4::getEncodingDependentString(FileContents &c, const long long &dur) const
{
    return c.getEncodingDependentString(four, dur);
}

QString Frame4::getEncodingDependentString(bool) const//фиктивный аргумент
{
    return FileHolder::getEncodingDependentString(four);
}

QString Frame4::getEncodingDependentString(bool, const long long &dur) const//фиктивный аргумент
{
    return FileHolder::getEncodingDependentString(four, dur);
}
