#include "v24.h"
#include "v1.h"
using namespace std;

Binary::Binary(const QString & path)
    : QFile(path)
{
    successfully_opened = QFile::open(QIODevice::ReadWrite | QIODevice::ExistingOnly);
    if (successfully_opened)
        seek(0);
}

Binary::Binary()
    : QFile()
{}

Binary::~Binary()
{
    close();
}

bool Binary::openf(const QString & path)
{
    setFileName(path);
    successfully_opened = QFile::open(QIODevice::ReadWrite | QIODevice::ExistingOnly);
    if (successfully_opened)
        seek(0);
    return successfully_opened;
}

Binary::operator bool() const
{
    return successfully_opened;
}

Binary & Binary::operator << (const string & s)
{
    write(s.c_str(),s.size());
    return *this;
}

Binary & Binary::operator << (char c)
{
    write(&c,1);
    return *this;
}

Binary & Binary::operator >> (char & c)
{
    getChar(&c);
    return *this;
}

const File_metadata & Binary::get_data() const
{
    return data;
}

File_metadata & Binary::get_data()
{
    return data;
}

bool Binary::has_info() const
{
    return data.has_info();
}

void Binary::shift(long long offset)
{
    long long destination = pos() + offset;

    if (destination >=0 || destination < size())
        seek(destination);
    else
    {
        if (destination < 0)
            seek(0);
        else
            seek(size() - 1);
    }
}

void Binary::one_byte_back_with_no_check()
{
    seek(pos() - 1);
}

QByteArray Binary::get_raw_bytes(bool unsynch, ulong amount)
{
    return ::get_raw_bytes(getChar_lambda
                           , unsynch
                           , one_byte_back_lambda
                           , amount);
}

QByteArray Binary::get_bytes(bool unsynch, ulong amount)
{
    return ::get_bytes(getChar_lambda
                        , unsynch
                        , one_byte_back_lambda
                        , amount);
}

char Binary::ch()
{
    return ::ch(getChar_lambda);
}

uchar Binary::get()
{
    return ::get(getChar_lambda);
}

char Binary::uch(bool unsynch)
{
    return ::uch(getChar_lambda
                 , unsynch
                 , one_byte_back_lambda);
}

uchar Binary::getb(bool unsynch)
{
    return ::getb(getChar_lambda
                  , unsynch
                  , one_byte_back_lambda);
}

Byte_order Binary::get_BOM(bool unsynch)
{
    return ::get_BOM(getChar_lambda
                     , unsynch
                     , one_byte_back_lambda);
}

QString Binary::get_iso8859_str(bool unsynch, const long long & dur)
{
    return ::get_iso8859_str(getChar_lambda
                             , unsynch
                             , one_byte_back_lambda
                             , dur);
}

QString Binary::get_utf16_str(bool unsynch, Byte_order bo, const long long & dur)//не чекает BOM
{
    return ::get_utf16_str(getChar_lambda
                           , unsynch
                           , bo
                           , one_byte_back_lambda
                           , dur);
}

QString Binary::get_utf8_str(bool unsynch, const long long & dur)
{
    return ::get_utf8_str(getChar_lambda
                          , unsynch
                          , one_byte_back_lambda
                          , dur);
}

QString Binary::get_ucs2_str(bool unsynch, Byte_order bo, const long long & dur)//не чекает BOM
{
    return ::get_ucs2_str(getChar_lambda
                          , unsynch
                          , bo
                          , one_byte_back_lambda
                          , dur);
}

QString Binary::get_encoding_dependent_string(bool unsynch, String_encoding enc, const long long & dur, function<bool()> skip_f)
{
    return ::get_encoding_dependent_string(getChar_lambda,unsynch,one_byte_back_lambda,dur,enc,skip_f);
}

void Binary::parse_from_start()
{
    seek(0);
    Tag_version v;
    do
    {
        v = v2_header();
        Parser v2(v,*this);
        v2.parse();
    } while (v != no_tag);
}

void Binary::parse_from_end()
{
    back_from_end(128);//перемещаемся на место предполагаемого тега v1
    if (check_for("TAG"))//перемещаемся на место предполагаемого футера
        back_from_end(138);
    else
        back_from_end(10);

    Tag_version v;
    qint64 len = 0;

    do
    {
        len = parse_v2_footer();//чекаем длину предполагаемого тега
        shift(-len - 20);//перемещаемся в начало предполагаемого тега
        v = v2_header();//чекаем идентификатор хедера предполагаемого тега
        Parser v2(v,*this);//создаём парсер для предполагаемого тега
        v2.parse();//парсим, если есть что парсить
        shift(-len - 20);//перемещаемся в место, где начинается футер предыдущего тега, если он есть
    } while (v != no_tag);
}

void Binary::parse_v1()
{
    if (data.needs_v1())
    {
        back_from_end(128);//перемещаемся на место предполагаемого тега v1
        if (check_for("TAG"))
        {
            Parser v1(*this);
            v1.parse();
        }
    }
}

bool Binary::parse()
{
    if (successfully_opened)
    {
        parse_from_start();
        parse_from_end();
        parse_v1();
        return data.has_info();
    }
    else
        return false;
}

void Binary::display_info(bool console) const
{
    if (console)
        data.display_on_console();
    else
        data.display_on_ui();
}

void Binary::back_from_end(qint64 offset)
{
    qint64 sz = size();
    if (offset <= sz)
        seek(sz - offset);
    else
        seek(0);
}

char Binary::ch_backwards()
{
    char c;
    getChar(&c);
    shift(-2);
    return c;
}

bool Binary::check_for(string value)
{
    char id[4];
    for (int i = 0;i < 3;++i)
        getChar(id + i);
    id[3] = 0;
    return !strcmp(id,value.c_str());
}

Tag_version Binary::v2_header()
{
    if (check_for("ID3"))
    {
        uchar version = get();
        if (get() != 255)
        {
            switch (version)
            {
            case 2:{return two;}
            case 3:{return three;}
            case 4:{return four;}
            default:{return no_tag;}
            }
        }
        else
            return no_tag;
    }
    else
        return no_tag;
}

ulong Binary::parse_v2_footer()//возвращает 0, если футер не найден или некорректен
{
    if (check_for("3DI"))
    {
        if (get() == 4)
        {
            if (get() != 255)
            {
                mByte flags = get();
                if (!flags[4])//если в футере указано, что футера нет
                    return 0;
                for (uint i = 0;i < 4;++i)
                    if (flags[i])//если проставлены неопределённые флаги
                        return 0;

                ulong len = 0;
                uchar c;
                for (int i = 3;i >= 0;--i)
                {
                    c = get();
                    if (c > 127)//выставлен msb
                        return 0;
                    else
                        len += c*power(128,i);
                }
                return len;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}
