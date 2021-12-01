#include "v22.h"
#include "frames2.h"
using namespace std;

bool Binary::V22::parse_header()
{
    Byte flags = get();
    unsynch = flags.test(7);
    bool correctness = set_length();
    end_position = start_position + 10 + length;
    if (correctness)
        correctness = !flags.test(6);//про все остальные биты в байте флагов в стандарте ничего не написано
    return correctness;
}

bool Binary::V22::set_length()
{
    unsigned char buf[4];
    for (int i = 3;i >= 0;--i)
        if ((buf[i] = get()) > 127)//если старший бит установлен в 1
            return false;

    for (int i = 3;i >= 0;--i)
        length += static_cast<unsigned long>(buf[i])*power(128,i);

    return true;
}

bool Binary::V22::parse()
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
