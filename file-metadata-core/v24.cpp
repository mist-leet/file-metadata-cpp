#include "v24.h"
#include "frames4RP.h"
using namespace std;

Binary::V24::V24(Binary &f)
    : Tag34(f)
{}

Binary::V24::~V24() = default;

bool Binary::V24::parse_header()//парсит расширенный заголовок, если он есть
{
    mByte flags = get();
    for (unsigned i = 0;i < 4;++i)
        if (flags.test(i))//если установлены неопределённые флаги
            return false;

    unsynch = flags.test(7);
    bool extdh = flags.test(6);
    experimental_tag = flags.test(5);
    footer_presence = flags.test(4);

    bool correctness = set_length([this](int &count)
                                    {
                                        return this->File_holder::get(count);
                                    }).second;
    if (footer_presence)
    {
        end_position = start_position + length + 20;
        extreme_position_of_frame = end_position - 21;
    }
    else
    {
        end_position = start_position + length + 10;
        extreme_position_of_frame = end_position - 11;
    }
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

    mByte flags = get(size_of_extended_header);

    update = flags.test(6);
    if (update)
        if (get(size_of_extended_header) != 0)
            return (update = false);

    expected_crc.second = flags.test(5);
    if (expected_crc.second)
        if (!set_crc())
            return (update = expected_crc.second = false);

    restrictions.presence = flags.test(4);
    if (restrictions.presence)
        if (!set_restrictions())
            return (update = expected_crc.second = restrictions.presence = false);

    return true;
}

bool Binary::V24::set_crc()
{    
    if (get(size_of_extended_header) != 5)
        return false;

    expected_crc.second = true;

    unsigned char buf[5];

    if ((buf[4] = get(size_of_extended_header)) > 15)
        expected_crc.second = false;

    for (int i = 3;i >= 0;--i)
        if ((buf[i] = get(size_of_extended_header)) > 127)
            expected_crc.second = false;

    if (expected_crc.second)
        for (int i = 4;i >= 0;--i)
            expected_crc.first += buf[i]*static_cast<unsigned long>(power(128,i));

    return true;
}

bool Binary::V24::set_restrictions()
{
    if (get(size_of_extended_header) != 1)
        return false;
    else
        restrictions.presence = true;

    mByte r = getb(size_of_extended_header);

    //ограничения размера и количества фреймов
    if (r.test(7))
    {
        restrictions.max_frames = 32;
        if (r.test(6))
            {restrictions.max_size = kbyte(4);}
        else
            {restrictions.max_size = kbyte(40);}
    }
    else
    {
        if (r.test(6))
        {
            restrictions.max_frames = 64;
            restrictions.max_size = kbyte(128);
        }
        if (!r.test(6))
        {
            restrictions.max_frames = 128;
            restrictions.max_size = mbyte();
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

bool Binary::V24::is_userdef_txt(const char * const id)
{
    return  (id[0] == 'T' && Binary::V24::correct_id(id) && strcmp(id, "TIT1") && strcmp(id, "TIT2") && strcmp(id, "TIT3")
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

bool Binary::V24::parse_data()
{
    bool fine_crc = true;
    if (expected_crc.second)
    {
        ulong data_len = end_position - pos();
        if (footer_presence)
            data_len -= 10;

        if (!content.set_data_and_check_src(file, unsynch, data_len, expected_crc.first))
        {
            qCritical() << "посчитанный CRC32 не совпадает с переданным\n";
            fine_crc = false;
        }
        else
        {
            extreme_position_of_frame = content.size() - 11;
        }
    }

    if (fine_crc)
    {
        while (pos() <= extreme_position_of_frame)
        {
            string frame_id = get_frame_id();
            Parser frame(frame_id.c_str(), *this);
            if (frame.parse() == no_id)
                shift(-3);
        }
    }

    if (!end())
        skip();
    return fine_crc;
}
