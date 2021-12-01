#include "frame3.h"
using namespace std;

Frame3::Frame3(Binary::V23 &t)
    : Frame34(t)
    , tag(t)
{
    if (tag.has_preextracted_data())
    {
        start_position = tag.get_content().pos() - 4;
        end_position = start_position + 4;
    }
}

Frame3::~Frame3() = default;

bool Frame3::parse_header()
{
    int number_of_length_bytes = set_length([this](int &count)
                                            {
                                                return this->getb(count);
                                            }).first;
    int extra_data_size = 0, number_of_flag_bytes = 0;

    data_length = length;

    mByte status = getb(number_of_flag_bytes);
    frame_status.tag_alter_preservation = !status.test(7);
    frame_status.file_alter_preservation = !status.test(6);
    frame_status.read_only = status.test(5);

    mByte format = getb(number_of_flag_bytes);

    end_position = start_position + 4 + number_of_length_bytes + number_of_flag_bytes + length;

    for (unsigned i = 0;i < 4;++i)
        if (format.test(i))
            return false;

    frame_format.compression_info.second = format.test(7);
    if (frame_format.compression_info.second)
        for (int i = 3;i >= 0;--i)
            frame_format.compression_info.first += static_cast<unsigned long>(getb(extra_data_size))*power(256,i);

    frame_format.encryption = format.test(6);
    if (frame_format.encryption)
    {
        uchar mark = getb(extra_data_size);
        if (Frame3::is_group_or_encr_mark(mark))
        {
            frame_format.encryption_method_marker = mark;
            frame_format.encryption = true;
        }
    }

    frame_format.group_id_presence = format.test(5);
    if (frame_format.group_id_presence)
    {
        uchar mark = getb(extra_data_size);
        if (Frame3::is_group_or_encr_mark(mark))
        {
            frame_format.group_id = mark;
            frame_format.group_id_presence = true;
        }
    }

    data_length -= extra_data_size;

    return true;
}

bool Frame3::set_string_encoding()
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
            encoding = ucs_2be;
            return true;
        case little_endian:
            encoding = ucs_2le;
            return true;
        case none:
            encoding = not_given;
            return false;
        }
    }

    default:
        encoding = not_given;
        return false;
    }
}

bool Frame3::is_group_or_encr_mark(uchar mark)
{
    return mark >= 128;
}

uchar Frame3::get_group_mark() const
{
    uchar mark = getb();
    if (Frame3::is_group_or_encr_mark(mark))
        return mark;
    else
        return 0;
}

bool Frame3::tag_has_content() const
{
    return tag.has_preextracted_data();
}

File_contents & Frame3::tags_content() const
{
    return tag.get_content();
}
