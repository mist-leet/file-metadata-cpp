#include "frame3.h"
using namespace std;

bool Binary::V23::Frame3::parse_frame_header()
{
    int frame_header_size = 4, extra_data_size = 0;

    for (int i = 3;i >= 0;--i)
        length += static_cast<unsigned long>(getb(frame_header_size))*power(256,i);
    data_length = length;

    Byte status = getb(frame_header_size);
    frame_status.tag_alter_preservation = !status.test(7);
    frame_status.file_alter_preservation = !status.test(6);
    frame_status.read_only = status.test(5);

    Byte format = getb(frame_header_size);

    end_position = start_position + frame_header_size + length;

    for (unsigned i = 0;i < 4;++i)
        if (format.test(i))
            return false;

    frame_format.raw_data.compression = format.test(7);
    if (frame_format.raw_data.compression)
    {
        frame_format.raw_data.raw_data_presence = true;
        for (int i = 3;i >= 0;--i)
            frame_format.raw_data.size += static_cast<unsigned long>(getb(extra_data_size))*power(256,i);
    }

    frame_format.encryption = format.test(6);
    if (frame_format.encryption)
    {
        frame_format.encryption_method_marker = getb(extra_data_size);
        frame_format.encryption = (frame_format.encryption_method_marker >= 128);
    }

    frame_format.group_id_presence = format.test(5);
    if (frame_format.group_id_presence)
    {
        frame_format.group_id = getb(extra_data_size);
        frame_format.group_id_presence = (frame_format.group_id >= 128);
    }

    data_length -= static_cast<unsigned long>(extra_data_size);

    return true;
}

bool Binary::V23::Frame3::parse_frame()
{
    if (parse_frame_header())
        return parse_frame_data();
    else
    {
        skip();
        return false;
    }
}
