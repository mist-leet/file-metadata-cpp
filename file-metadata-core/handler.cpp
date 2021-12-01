#include "handler.h"
using namespace std;
/*
//вставляет строку str с позиции bias
void binaryfile::insert(const string & str, const li & bias)
{
    if (bias <= size)//если не выходит за пределы файла
    {
        const int strsize = str.size();
        if (this->size - bias >= strsize)//если нужно сместить полную строку 1 или более раз
        {
            li pos = this->size, seekpos = 0;
            int len = strsize;
            char * buf_c = new char [strsize + 1];
            bool continue_ = true;
            for (; (pos > bias - strsize) & continue_; pos -= strsize)
            {//идёт с конца, берёт строчку и переносит её на strsize символов вперёд
                seekpos = pos - len;
                if (seekpos < bias)
                {
                    len = pos - bias;
                    pos = bias + strsize;
                    seekpos = bias;
                    continue_ = false;
                }
                seekg(seekpos,ios::beg);
                read(buf_c,len);
                buf_c[len] = '\0';
                seekp(pos,ios::beg);
                cout << "1: going to put '" << buf_c << "' from " << tellg() << " pos\n";
                *this << buf_c;
            }
            seekp(bias,ios::beg);
            cout << "1: going to put '" << str << "' from " << tellg() << " bias = " << bias << '\n';
            *this << str;
            delete[] buf_c;
        }
        else
        {//переносит только одну строчку
            char * buf_c = new char[this->size - bias + 1];
            seekg(bias,ios::beg);
            read(buf_c,size - bias);
            buf_c[size - bias] = '\0';
            seekp(bias,ios::beg);
            *this << str;
            seekp(bias + strsize,ios::beg);
            cout << "2: going to put '" << buf_c << "' from " << tellg() << " pos\n";
            *this << buf_c;
            delete[] buf_c;
        }
    }
}

//парсит файл
void binaryfile::parse_file()
{
    //Минимальный размер ID3-тега - 21 байт. Из них первые 3 - это символы "ID3".
    //То есть нужно пропарсить первые (size - 21) байт на наличие ID3-тега
    char buff_c[len_of_id3_identifier+1];
    seekg(0,ios::beg);
    while (tellg() <= size - min_id3_tag_len)
    {
        read(buff_c, len_of_id3_identifier);
        buff_c[3] = 0;
        if (!strcmp(buff_c,"ID3"))
            handle_id3v2_tag();
        else
            get();
    }
}

//проверяет, является ли строка заголовком фрейма, если да, то парсит соответствующий фрейм
bool binaryfile::parse_frame_24(const char * const id)//id должен ОБЯЗАТЕЛЬНО быть 0-терминирован
{
    switch (id[0])
    {
    case 'T'://группа текстовых фреймов
        if (check_str(id + 1))//если символы окажутся не заголовком фрейма
            if (parse_text_frame(id))//или фрейм окажется сломанным
                break;//то организуется fall through до default

    case 'W'://группа фреймов, содержащих URL
        if (check_str(id + 1))
            if (parse_url_frame(id))
                break;

    case 'M':
        if (!strcmp(id,"MCDI"))
        {
            if (parse_MCDI())
                break;
        }
        else if (!strcmp(id,"MLLT"))
        {
                if (parse_MLLT())
                    break;
        }

    case 'E':
        if (!strcmp(id,"ETCO"))
        {
            if (parse_ETCO())
                break;
        }
        else if (!strcmp(id,"EQU2"))
        {
            if (parse_EQU2())
                break;
        }
        else if (!strcmp(id,"ENCR"))
        {
            if (parse_ENCR())
                break;
        }

    case 'S':
        if (!strcmp(id,"SYTC"))
        {
            if (parse_SYTC())
                break;
        }
        else if (!strcmp(id,"SYLT"))
        {
            if (parse_SYLT())
                break;
        }
        else if (!strcmp(id,"SIGN"))
        {
            if (parse_SIGN())
                break;
        }
        else if (!strcmp(id,"SEEK"))
        {
            if (parse_SEEK())
                break;
        }

    case 'U':
        if (!strcmp(id, "USLT"))
        {
            if (parse_USLT())
                break;
        }
        else if (!strcmp(id,"USER"))
        {
            if (parse_USER())
                break;
        }

    case 'C':
        if (!strcmp(id,"COMM"))
        {
            if (parse_COMM())
                break;
        }
        else if (!strcmp(id,"COMR"))
        {
            if (parse_COMR())
                break;
        }

    case 'R':
        if (!strcmp(id,"RVA2"))
        {
            if (parse_RVA2())
                break;
        }
        else if (!strcmp(id,"RVRB"))
        {
            if (parse_RVRB())
                break;
        }
        else if (!strcmp(id,"RBUF"))
            if (parse_RBUF())
                break;

    case 'A':
        if (!strcmp(id,"APIC"))
        {
            if (parse_APIC())
                break;
        }
        else if (!strcmp(id,"AENC"))
        {
            if (parse_AENC())
                break;
        }
        else if (!strcmp(id,"ASPI"))
            if (parse_ASPI())
                break;

    case 'P':
        if (!strcmp(id,"PCNT"))
        {
            if (parse_PCNT())
                break;
        }
        else if (!strcmp(id,"POPM"))
        {
            if (parse_POPM())
                break;
        }
        else if (!strcmp(id,"POSS"))
        {
            if (parse_POSS())
                break;
        }
        else if (!strcmp(id,"PRIV"))
        {
            if (parse_unknown_frame())
                break;
        }

    case 'G':
        if (!strcmp(id,"GRID"))
        {
            if (parse_GRID())
                break;
        }
        else if (!strcmp(id,"GEOB"))
        {
            if (parse_GEOB())
                break;
        }

    case 'L':
        if (!strcmp(id,"LINK"))
            if (parse_LINK())
                break;

    case 'O':
        if (!strcmp(id,"OWNE"))
            if (parse_OWNE())
                break;

    case 'X':
    case 'Y':
    case 'Z':
        if (check_str(id + 1))
            if (parse_unknown_frame())
                break;

    default:
        seekg(-3,ios::cur);
    }
}

//проверяет, может ли символ входить в заголовок фрейма
bool check_char(char c)
{
    if ((c >= 'A' & c <= 'Z') | (c >= '0' & c <= '9'))
        return true;
    else
        return false;
}

//проверяет, может ли строка являться заголовком или частью заголовка фрейма
bool check_str(const char * const s)
{
    for (int i = 0;i < 5;++i)
    {
        if (s[i] == 0)
            return true;
        else if (!check_char(s[i]))
            return false;
    }
    return false;
}

//парсит текстовый фрейм, возвращает true, если парсинг прошёл успешно (фрейм не поломан)
bool binaryfile::parse_text_frame(const char * const)
{

}

//парсит URL-фрейм, возвращает true, если парсинг прошёл успешно (фрейм не поломан)
bool binaryfile::parse_url_frame(const char * const)
{

}

//
bool binaryfile::parse_MCDI()
{

}

//
bool binaryfile::parse_MLLT()
{

}

//
bool binaryfile::parse_ETCO()
{

}

//
bool binaryfile::parse_EQU2()
{

}

//
bool binaryfile::parse_ENCR()
{

}

//
bool binaryfile::parse_SYTC()
{

}

//
bool binaryfile::parse_SYLT()
{

}

//
bool binaryfile::parse_SIGN()
{

}

//расстояние от конца данного тега до начала следующего
bool binaryfile::parse_SEEK()//пока только для v2.4
{
    pair<Frame_header,bool> header = parse_frame_header(4);
    if (!header.second)
        return false;
    else
    {
        if (tag.t_unique_frames.find("SEEK") == tag.t_unique_frames.end())//если это первый SEEK в теге
        {
            tag.t_offset_to_next_tag.first = static_cast<unsigned long>(getb(header.first.f_unsynch))*256*256*256 +
                                             static_cast<unsigned long>(getb(header.first.f_unsynch))*256*256 +
                                             static_cast<unsigned long>(getb(header.first.f_unsynch))*256 +
                                             static_cast<unsigned long>(getb(header.first.f_unsynch));
            tag.t_offset_to_next_tag.second = true;
            tag.t_unique_frames.insert("SEEK");
            return true;
        }
        else//если не первый SEEK, переезжаем в начало следующего фрейма
        {
            seekg(header.first.f_size,ios::cur);
            return false;//если в нарушение стандарта в теге появятся более 1 фрейма SEEK, то учтён будет только первый,
        }                //хотя это, возможно, не совсем логично
    }//по стандарту в фрейме должно быть только 4 значащих байта, хранящие отступ до следующего тега.
}    //впоследствии можно добавить обработку некорректного фрейма

//
bool binaryfile::parse_USLT()
{

}

//
bool binaryfile::parse_USER()
{

}

//
bool binaryfile::parse_COMM()
{

}

//
bool binaryfile::parse_COMR()
{

}

//
bool binaryfile::parse_RVA2()
{

}

//
bool binaryfile::parse_RVRB()
{

}

//
bool binaryfile::parse_RBUF()
{

}

//
bool binaryfile::parse_APIC()
{

}

//
bool binaryfile::parse_AENC()
{

}

//
bool binaryfile::parse_ASPI()
{

}

//
bool binaryfile::parse_PCNT()
{

}

//
bool binaryfile::parse_POPM()
{

}

//
bool binaryfile::parse_POSS()
{

}

//
bool binaryfile::parse_GRID()
{

}

//
bool binaryfile::parse_GEOB()
{

}

//
bool binaryfile::parse_LINK()
{

}

//
bool binaryfile::parse_OWNE()
{

}

//поскольку смысл содержимого такого фрейма неизвестен, функция просто переставляет файловый указатель в начало некст фрейма
//также применяется для парсинга фрейма PRIV, так как его содержимое тоже неизвестно
bool binaryfile::parse_unknown_frame()//пока только для v2.4
{//необходимости парсить весь заголовок нет, хотя впоследствии можно добавить проверку, не выставлены ли неопределённые флаги
    char buf[4];
    for (int i = 0;i < 4;++i)
        buf[i] = getb();
    pair<bitset<28>,bool> len = synchsafe_handler(buf);
    if (len.second)
    {
        seekg(len.first.to_ulong(),ios::cur);
        return true;
    }
    else
        return false;
}
*/
