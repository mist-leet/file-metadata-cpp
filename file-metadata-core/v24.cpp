#include "v24.h"
#include "frames4.h"
using namespace std;

bool Binary::V24::parse_header()//также парсит расширенный заголовок, если он есть
{
    Byte flags = get();
    for (unsigned i = 0;i < 4;++i)
        if (flags.test(i))//если установлены неопределённые флаги
            return false;

    unsynch = flags.test(7);
    bool extdh = flags.test(6);
    experimental_tag = flags.test(5);
    footer_precense = flags.test(4);

    bool correctness = set_length();
    end_position = start_position + 10 + length;
    if (footer_precense)
        end_position += 10;
    if (correctness && extdh)
        correctness = parse_extended_header();
    return correctness;
}

bool Binary::V24::parse_extended_header()
{
    for (int i = 0;i < 4;++i)//длину тега можно узнать другим образом, поэтому байты длины можно игнорировать
        if (get(size_of_extended_header) > 127)
            return false;

    if (get(size_of_extended_header) != 1)//в стандарте определено только значение 1
        return false;

    Byte flags = get(size_of_extended_header);

    tag_is_an_update = flags.test(6);
    if (tag_is_an_update)
        if (get(size_of_extended_header) != 0)
            return (tag_is_an_update = false);

    CRC32.second = flags.test(5);
    if (CRC32.second)
        if (!set_crc())
            return (tag_is_an_update = CRC32.second = false);

    restrictions.precense = flags.test(4);
    if (restrictions.precense)
        if (!set_restrictions())
            return (tag_is_an_update = CRC32.second = restrictions.precense = false);

    return true;
}

bool Binary::V24::set_crc()//CRC32 хранится в synchsafe байтах, поэтому используется get()
{    
    if (get(size_of_extended_header) != 5)
        return false;

    CRC32.second = true;

    unsigned char buf[5];

    if ((buf[4] = get(size_of_extended_header)) > 15)
        CRC32.second = false;

    for (int i = 3;i >= 0;--i)
        if ((buf[i] = get(size_of_extended_header)) > 127)
            CRC32.second = false;

    if (CRC32.second)
        for (int i = 4;i >= 0;--i)
            CRC32.first = static_cast<unsigned long>(buf[i])*static_cast<unsigned long>(power(128,i));

    return true;
}

bool Binary::V24::set_restrictions()
{
    if (get(size_of_extended_header) != 1)//на байте с длиной не может возникнуть false synch
        return false;
    else
        restrictions.precense = true;

    Byte r = getb(size_of_extended_header);
    //ограничения размера и количества фреймов
    if (r.test(7))
    {
        restrictions.max_frames = 32;
        restrictions.max_size = 4*1024;
        if (!r.test(6))
            restrictions.max_size *= 10;
    }
    else
    {
        restrictions.max_frames = 64;
        restrictions.max_size = 128*1024;
        if (!r.test(6))
        {
            restrictions.max_frames *= 2;
            restrictions.max_size *= 8;
        }
    }
    //ограничения по кодировке текста
    restrictions.encoding_rest = r.test(5);
    //ограничения по количеству символов в одном фрейме
    if (r.test(4))
    {
        if (r.test(3))
            restrictions.max_char_per_frame = 30;
        else
            restrictions.max_char_per_frame = 128;
    }
    else //по дефолту стоит максимально возможный размер
        if (r.test(3))
            restrictions.max_char_per_frame = 1024;
    //ограничения по кодировке изображений
    restrictions.image_encoding_rest = r.test(2);
    //ограничения по размеру изображений
    restrictions.image_size_rest = make_pair(r.test(1),r.test(0));

    return true;
}

bool Binary::V24::parse()
{
    if (parse_header())
    {
        //парсить фреймы
    }
    else
    {
        skip();
        return false;
    }
}
