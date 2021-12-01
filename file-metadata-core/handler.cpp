#pragma once
#include "pch.h"
#include "handler.h"
using namespace std;

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
                *this << buf_c;
            }
            seekp(bias,ios::beg);
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
            *this << buf_c;
            delete[] buf_c;
        }
    }
}

//устанавливает длину файла в байтах, оставляя файловый указатель на том же месте
li binaryfile::get_size()
{
    li current = tellg();
    seekg(0,ios::end);
    li fsize = tellg();
    seekg(current,ios::beg);
    return fsize;
}

//переводит 4-байтный synchsafe int (bitset<32>) в двоичную запись обычного int
pair<bitset<28>,bool> synchsafe_handler(const bitset<32> & s_safe)
{
    bitset<28> val;
    for (unsigned i = 7;i < 32;i += 8)
        if (s_safe[i])
            return make_pair(val,false);//если старший бит любого байта установлен в 1, то запись некорректна, тег нечитабелен
    for (unsigned i = 0;i < 28;++i)
        val[i] = s_safe.test(i + i / 7);
    return make_pair(val,true);
}

//принимает массив символов и переводит первые четыре в bitset<32>, затем в bitset<28>
pair<bitset<28>,bool> synchsafe_handler(const char * const text)
{
    Byte binary_text[4];
    for (int i = 0;i < 4;++i)
        binary_text[i] = text[i];
    bitset<32> binary_text_1;
    for (int i = 0;i < 32;++i)
        binary_text_1[i] = binary_text[i / 8][i % 8];
    return synchsafe_handler(binary_text_1);
}

//устанавливает флаг correct, сбрасывает все остальные флаги; вызывается при парсинге нового тега
void Tag::set_to_initial_state()
{
    correct = true;
    unsynch = experimental = footer = extd_data.first.CRC32.second = extd_data.first.update = t_count =
    extd_data.first.restrictions.second = extd_data.first.padding_size.second = extd_data.second = false;
}

//определяет CRC-32 для тега v2.4
void binaryfile::get_CRC32_v24()
{
    bitset<40> s_safe;
    Byte byte;
    for (int i = 0;i < 5;++i)
    {
        byte = getb(tag.t_count);
        for (int j = 0;j < 8;++j)
            s_safe[(4 - i)*8 + j] = byte[j];
    }

    for (int i = 7;i < 40;i += 8)
        if (s_safe[i])
        {
            tag.extd_data.first.CRC32.second = false;
            return;
        }

    tag.extd_data.first.CRC32.second = true;
    for (int i = 0;i < 32;++i)
        tag.extd_data.first.CRC32.first[i] = s_safe.test(i + i/7);
}

//определяет ограничения для тега v2.4
void binaryfile::get_restrictions_v24()
{
    Byte r = getb(tag.t_count);
    tag.extd_data.first.restrictions.second = true;
    //ограничения на размер изображений
    if (r[1])
    {
        if (r[0])
        {//11
            tag.extd_data.first.restrictions.first.pic_size_rest = true;
            tag.extd_data.first.restrictions.first.max_pic_size = 64;
            tag.extd_data.first.restrictions.first.min_pic_size = 64;
        }
        else
        {//10
            tag.extd_data.first.restrictions.first.pic_size_rest = true;
            tag.extd_data.first.restrictions.first.max_pic_size = 64;
            tag.extd_data.first.restrictions.first.min_pic_size = 0;
        }
    }
    else
    {
        if (r[0])
        {//01
            tag.extd_data.first.restrictions.first.pic_size_rest = true;
            tag.extd_data.first.restrictions.first.max_pic_size = 256;
            tag.extd_data.first.restrictions.first.min_pic_size = 0;
        }
        else//00
            tag.extd_data.first.restrictions.first.pic_size_rest = false;
    }
    //ограничения на формат изображений
    if (r[2])//1
        tag.extd_data.first.restrictions.first.pic_type_rest = true;
    else//0
        tag.extd_data.first.restrictions.first.pic_type_rest = false;
    //ограничения на размер текстовых полей
    if (r[4])
    {
        if (r[3])//11
            tag.extd_data.first.restrictions.first.max_char_per_frame = 30;
        else//10
            tag.extd_data.first.restrictions.first.max_char_per_frame = 128;
    }
    else
    {
        if (r[3])//01
            tag.extd_data.first.restrictions.first.max_char_per_frame = 1024;
        else//00
            tag.extd_data.first.restrictions.first.max_char_per_frame = 268435445;
    }
    //ограничения на кодировку текста
    if (r[5])//1
        tag.extd_data.first.restrictions.first.encoding_rest = true;
    else//0
        tag.extd_data.first.restrictions.first.encoding_rest = false;
    //ограничения на размер тега
    if (r[7])
    {
        if (r[6])
        {//11
            tag.extd_data.first.restrictions.first.max_frames = 32;
            tag.extd_data.first.restrictions.first.max_size = 4096;//4 kb
        }
        else
        {//10
            tag.extd_data.first.restrictions.first.max_frames = 32;
            tag.extd_data.first.restrictions.first.max_size = 40960;//40 kb
        }
    }
    else
    {
        if (r[6])
        {//01
            tag.extd_data.first.restrictions.first.max_frames = 64;
            tag.extd_data.first.restrictions.first.max_size = 131072;//128 kb
        }
        else
        {//00
            tag.extd_data.first.restrictions.first.max_frames = 128;
            tag.extd_data.first.restrictions.first.max_size = 1048576;//1 Mb
        }
    }
}

//обрабатывает расширенный хедер в v2.4
void binaryfile::parse_extd_h_4()
{
    for (int i = 0;i < 5;++i)
        getb(tag.t_count);
    Byte flags = getb(tag.t_count);
    if (flags[6])
    {
        getb(tag.t_count);
        tag.extd_data.first.update = true;
    }
    if (flags[5])
    {
        getb(tag.t_count);
        get_CRC32_v24();
    }
    if (flags[4])
    {
        getb(tag.t_count);
        get_restrictions_v24();
    }
}

//обрабатывает расширенный хедер в v2.3
void binaryfile::parse_extd_h_3()
{
    for (int i = 0;i < 4;++i)
        getb(tag.t_count);
    Byte f = getb(tag.t_count);
    bool crc_present = f[7];
    getb(tag.t_count);

    Byte buffer_arr[4];
    for (int i = 0;i < 4;++i)
        buffer_arr[i] = getb(tag.t_count);

    bitset<32> padding_size;
    for (int i = 31;i >= 0;--i)
        padding_size[i] = buffer_arr[i / 8][i % 8];

    tag.extd_data.first.padding_size.second = true;
    tag.extd_data.first.padding_size.first = padding_size.to_ulong();

    if (crc_present)
    {
        for (int i = 0;i < 4;++i)
            buffer_arr[i] = getb(tag.t_count);
        for (int i = 31;i >= 0;--i)
            tag.extd_data.first.CRC32.first[i] = buffer_arr[i / 8][i % 8];
        tag.extd_data.first.CRC32.second = true;
    }
}

//обрабатывает хедер
bool binaryfile::parse_header(int version)
{
    //чтение флагов
    Byte flags = getb(tag.t_count);
    cout << "flags: " << flags << '\n';
    for (int i = 0;i < 4;++i)
        if (flags[i])
        {
            tag.correct = false;
            return false;//если установлены неопределённые флаги, то тег нечитаем
        }
    tag.unsynch = flags[7];
    switch (version)
    {
        case 2:
            for (int i = 4;i < 7;++i)
                if (flags[i])
                {
                    tag.correct = false;
                    return false;//если установлены неопределённые флаги, то тег нечитаем
                }
            break;
        case 3:
            if (flags[4])
            {
                tag.correct = false;
                return false;//если установлен неопределённый флаг, то тег нечитаем
            }
            tag.extd_data.second = flags[6];
            tag.experimental = flags[5];
            break;
        case 4:
            tag.extd_data.second = flags[6];
            tag.experimental = flags[5];
            tag.footer = flags[4];
            break;
    }
    //чтение длины
    char s_safe_len[4];
    for (int i = 0;i < 4;++i)
        s_safe_len[i] = getb(tag.t_count);
    pair<bitset<28>,bool> binary_len = synchsafe_handler(s_safe_len);
    if (!binary_len.second)
    {
        tag.correct = false;
        return false;//если не соблюдена synchsafety в байтах длины, тег считается нечитабельным
    }
    tag.len = binary_len.first.to_ulong();
    cout << "len = " << tag.len / pow(2,20) << " Mb\n";
    //чтение расширенного заголовка
    if (tag.extd_data.second)
        switch(version)
        {
            case 3:
                parse_extd_h_3();
                break;
            case 4:
                parse_extd_h_4();
                break;
        }
    return true;
}

//обрабатывает тег ID3v2.2
void binaryfile::handle_v22()
{
    if (!parse_header(2))
        return;
    cout << "header is correct\n";
}

//обрабатывает тег ID3v2.3
void binaryfile::handle_v23()
{
    if (!parse_header(3))
        return;
    cout << "header is correct\n";
}

//обрабатывает тег ID3v2.4
void binaryfile::handle_v24()
{
    if (!parse_header(4))
        return;
    cout << "header is correct\n";

    tag.start_pos = tellg();
    char ID[id3_frame_ID_len + 1];
    while (tellg() <= tag.start_pos + tag.len - min_id3_frame_len)
    {
        read(ID,id3_frame_ID_len);//нужно вернуться назад на 3 символа, чтобы всё прочекать
        seekg(-3,ios::cur);//возвращаемся на 3 символа назад, чтобы ничего не пропустить; вообще, это нужно делать где нибудь в другом месте
        ID[4] = 0;
        parse_frame(ID);
    }

}

//обрабатывает тег ID3v2
void binaryfile::handle_id3v2_tag()
{
    tag.set_to_initial_state();
    int version = getb(tag.t_count);
    cout << "vers: " << version << '\n';
    int revision = getb(tag.t_count);//ревизии имеют обратную совместимость, поэтому их необязательно сохранять
    if (revision < 255)
        switch (version)
        {
            case 2:
                handle_v22();
                break;
            case 3:
                handle_v23();
                break;
            case 4:
                handle_v24();
                break;
        }
}

//возвращает байт из тега с учётом десинхронизации: для v2.2 и v2.3, а также для v2.4, если все фреймы десинхронизированы
int binaryfile::getb()
{
    return getb(tag.unsynch);//насколько я понял, член класса не может быть параметром по умолчанию
}

//возвращает байт с учётом десинхронизации
int binaryfile::getb(bool unsynch)
{
    if (unsynch)
    {
        int current_byte = get(), next_byte = get();//берём текущий и сразу следующий байт
        tag.t_count += 2;//считали 2 байта
        if (current_byte != 255 | next_byte != 0)//если байты не являются 0xFF 0x00
        {
            --tag.t_count;//считали только 1 байт
            seekg(-1,ios::cur);//возвращаемся на позицию назад, как будто не считывали второй байт
        }
        return current_byte;
    }
    else
    {
        ++tag.t_count;
        return get();
    }
}

//парсит файл
void binaryfile::parse()
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

//парсит фрейм
bool binaryfile::parse_frame(const char * const ID)
{
    return 0;
}

//возвращает числовое значение двух байтов из тега с учётом порядка бит и десинхронизации
unsigned binaryfile::get2b(char byteorder = 'B')//B - big-endian, L - little-endian
{
    return get2b(tag.unsynch, byteorder);
}

//возвращает числовое значение двух байтов с учётом порядка бит и десинхронизации (только для v2.4)
unsigned binaryfile::get2b(bool unsynch, char byteorder = 'B')//BE - big-endian, L - little-endian
{
    unsigned first = getb(unsynch), second = getb(unsynch);
    if (byteorder == 'B')
        return first*256 + second;
    else
        return second*256 + first;
}

//возвращает метку порядка байтов, флаг десинхронизации берётся из свойств тега
char binaryfile::getBOM()//возвращает 'B', если big-endian, 'L', если little-endian, '0', если BOM отсутствует
{
    return getBOM(tag.unsynch);
}

//возвращает метку порядка байтов
char binaryfile::getBOM(bool unsynch)//возвращает 'B', если big-endian, 'L', если little-endian, '0', если BOM отсутствует
{
    int first = getb(unsynch), second = getb(unsynch);
    if (first == 254 & second == 255)
        return 'B';
    else if (first == 255 & second == 254)
        return 'L';
    else return '0';
}

//возвращает десятеричный код символа из UTF-8, флаг десинхронизации берётся из свойств тега
long binaryfile::utf8()
{
    return utf8(tag.unsynch);
}

//возвращает десятеричный код символа из UTF-8
long binaryfile::utf8(bool unsynch)
{
    Byte byte1 = getb(unsynch);
    if (byte1[7])
    {
        Byte byte2 = getb(unsynch);
        if (byte1[5])
        {
            Byte byte3 = getb(unsynch);
            if (byte1[4])
            {
                Byte byte4 = getb(unsynch);
                bitset<21> value;
                for (int i = 20;i > 17;--i)
                    value[i] = byte1[i - 18];
                for (int i = 17;i > 11;--i)
                    value[i] = byte2[i - 12];
                for (int i = 11;i > 5;--i)
                    value[i] = byte3[i - 6];
                for (int i = 5;i >= 0;--i)
                    value[i] = byte4[i];
                return value.to_ulong();
            }
            else
            {
                bitset<16> value;
                for (int i = 15;i > 11;--i)
                    value[i] = byte1[i - 12];
                for (int i = 11;i > 5;--i)
                    value[i] = byte2[i - 6];
                for (int i = 5;i >= 0;--i)
                    value[i] = byte3[i];
                return value.to_ulong();
            }
        }
        else
        {
            bitset<11> value;
            for (int i = 10;i > 5;--i)
                value[i] = byte1[i - 6];
            for (int i = 5;i >= 0;--i)
                value[i] = byte2[i];
            return value.to_ulong();
        }
    }
    else
    {
        return byte1.to_ulong();
    }
}
