#include "v23.h"
#include "frames3.h"
using namespace std;

bool Binary::V23::parse_header()
{
    Byte flags = get();
    for (unsigned i = 0;i < 5;++i)
        if (flags.test(i))//если установлены неопределённые флаги
            return false;

    unsynch = flags.test(7);
    bool extdh = flags.test(6);
    experimental_tag = flags.test(5);

    bool correctness = set_length();
    end_position = start_position + 10 + length;
    if (correctness && extdh)
        correctness = parse_extended_header();
    return correctness;
}

bool Binary::V23::parse_extended_header()
{
    unsigned long size = 0;
    for (int i = 3;i >= 0;--i)
        size += static_cast<unsigned long>(getb(size_of_extended_header))*power(256,i);

    if (size < 6)
        return false;

    long long previous_position = pos();

    CRC32.second = (getb(size_of_extended_header) > 127);//установлен первый бит первого флага

    if (CRC32.second && size < 10)
        return false;

    getb(size_of_extended_header);//второй байт не имеет значимого контента
    size_of_padding.second = true;
    for (int i = 3;i >= 0;--i)
        size_of_padding.first += static_cast<unsigned long>(getb(size_of_extended_header))*power(256,i);


    if (CRC32.second)
        for (int i = 3;i >= 0;--i)
            CRC32.first += static_cast<unsigned long>(getb(size_of_extended_header))*power(256,i);

    while (pos() < previous_position + size)
        get(size_of_extended_header);
    //все эти пляски - на случай некорректного заголовка
    return true;
}

bool Binary::V23::parse()
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
