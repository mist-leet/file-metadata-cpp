#include "frame4.h"
using namespace std;

Frame4::Frame4(Binary::V24 &t)
    : Frame34(t)
    , tag(t)
{
    synchsafe_header = true;
    if (tag.has_preextracted_data())
    {
        start_position = tag.get_content().pos() - 4;
        end_position = start_position + 4;
    }
}

Frame4::~Frame4() = default;

bool Frame4::is_group_or_encr_mark(uchar c)
{
    return c >= 128 && c <= 240;
}

uchar Frame4::get_group_mark() const
{
    uchar mark = getb();
    if (Frame4::is_group_or_encr_mark(mark))
        return mark;
    else
        return 0;
}

bool Frame4::parse_header()
{//функция начинает работу после frame ID
    if (!set_length([this](int &count)
                    {
                        return this->get(count);
                    }).second)
        return false;

    data_length = length;

    end_position = start_position + 10 + length;

    mByte status = getb();//неопределённые флаги могут быть выставлены, это не ошибка

    frame_status.tag_alter_preservation = !status.test(6);
    frame_status.file_alter_preservation = !status.test(5);
    frame_status.read_only = status.test(4);

    mByte format = get();//неопределённые флаги не должны быть выставлены
    if (format.test(7) || format.test(5) || format.test(4))
        return false;

    int extra_data_size = 0;

    frame_format.group_id_presence = format.test(6);
    if (frame_format.group_id_presence)
    {
        uchar mark = get(extra_data_size);
        if (Frame4::is_group_or_encr_mark(mark))
            frame_format.group_id = mark;
        else
            frame_format.group_id_presence = false;
    }

    if (format.test(3))
    {
        if (format.test(0))
            frame_format.compression_info.second = true;
        else
            return false;
    }

    frame_format.encryption = format.test(2);
    if (frame_format.encryption)
    {
        uchar mark = get(extra_data_size);
        if (Frame4::is_group_or_encr_mark(mark))
            frame_format.encryption_method_marker = mark;
        else
            frame_format.encryption = false;
    }

    unsynch = format.test(1);

    if (frame_format.compression_info.second || format.test(0))
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
                frame_format.compression_info.first += static_cast<unsigned long>(buf[i])*power(128,i);
    }

    data_length -= extra_data_size;

    return true;
}

bool Frame4::set_string_encoding()
{
    uchar enc_byte = getb();
    switch (enc_byte)
    {
    case 0:
        encoding = iso_8859_1;
        return true;

    case 1:
    {
        Byte_order bo = get_BOM();
        switch (bo)
        {
        case big_endian:
            encoding = utf_16be;
            return true;

        case little_endian:
            encoding = utf_16le;
            return true;

        case none:
            encoding = not_given;
            return false;
        }
    }

    case 2:
        encoding = utf_16be;
        return true;

    case 3:
        encoding = utf_8;
        return true;

    default:
        encoding = not_given;
        return false;
    }
}

bool Frame4::tag_has_content() const
{
    return tag.has_preextracted_data();
}

File_contents & Frame4::tags_content() const
{
    return tag.get_content();
}
