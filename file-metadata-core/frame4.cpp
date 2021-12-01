#include "frame4.h"
using namespace std;

/*----------------------------------------------------------------------------
 * Если функция возвращает false, то:
 * a) data_length == 0:
 *      тег парсится дальше посимвольно начиная с текущей позиции;
 * b) data_length != 0:
 *      файловый указатель смещается на data_length байтов вперёд,
 *      тег парсится со следующего фрейма, если он находится на ожидаемой позиции,
 *      или дальше посимвольно.
 ---------------------------------------------------------------------------*/
bool Binary::V24::Frame4::parse_frame_header()
{//функция начинает работу после frame ID
    if (!set_length())
        return false;

    Byte status = get();//неопределённые флаги могут быть выставлены

    frame_status.tag_alter_preservation = !status.test(6);
    frame_status.file_alter_preservation = !status.test(5);
    frame_status.read_only = status.test(4);

    Byte format = get();
    //проверка на undefined флаги
    if (format.test(7) || format.test(5) || format.test(4))
        return false;

    int extra_data_size = 0;

    frame_format.group_id_presence = format.test(6);
    if (frame_format.group_id_presence)
    {
        frame_format.group_id = get(extra_data_size);//group id не может вызвать false synch
        frame_format.group_id_presence = (frame_format.group_id >= 128 && frame_format.group_id <= 240);
        if (frame_format.group_id == 255)
            return false;
    }

    if (format.test(3))
    {
        if (format.test(0))
            frame_format.raw_data.compression = true;
        else
            return false;
    }

    frame_format.encryption = format.test(2);
    if (frame_format.encryption)
    {
        frame_format.encryption_method_marker = get(extra_data_size);//encryption method marker не может вызвать false synch
        frame_format.encryption = (frame_format.encryption_method_marker >= 128 && frame_format.encryption_method_marker <= 240);
        if (frame_format.encryption_method_marker == 255)
            return false;
    }

    unsynch = format.test(1);

    frame_format.raw_data.raw_data_presence = format.test(0);
    if (frame_format.raw_data.raw_data_presence)
    {
        unsigned char buf[4];
        for (int i = 3;i >= 0;--i)
            if ((buf[i] = get(extra_data_size)) > 127)//raw data size хранится в synchsafe int
            {
                frame_format.raw_data.raw_data_presence = false;
                if (buf[i] == 255)
                    return false;
            }

        if (frame_format.raw_data.raw_data_presence)
            for (int i = 3;i >= 0;--i)
                frame_format.raw_data.size += static_cast<unsigned long>(buf[i])*power(128,i);
    }

    data_length -= static_cast<unsigned long>(extra_data_size);

    return true;
}

bool Binary::V24::Frame4::set_length()
{
    unsigned char buf[4];
    for (int i = 3;i >= 0;--i)
        if ((buf[i] = get()) > 127)
            return false;

    for (int i = 3;i >= 0;--i)
        length += static_cast<unsigned long>(buf[i])*power(128,i);
    data_length = length;

    end_position = start_position + 10 + length;

    return true;
}
