#pragma once
#include "frame_structs.h"
#include "tag_structs.h"
#include "file_structs.h"
#include "char_extracting.h"
using namespace std;

class Binary : public QFile
{
    Binary(const Binary &) = delete;
    Binary& operator = (const Binary &) = delete;

    void one_byte_back_with_no_check();

protected:
    bool successfully_opened{false};
    File_metadata data{};

    function<bool(char *)> getChar_lambda{
                                            [this](char * c)
                                            {
                                                return this->getChar(c);
                                            }
                                         };

    function<void()> one_byte_back_lambda{
                                            [this]()
                                            {
                                                return this->one_byte_back_with_no_check();
                                            }
                                         };

public:
    class V1;
    class V22;
    class V23;
    class V24;
    //friend class ::Parser;

    explicit Binary(const QString &);

    Binary();

    bool openf(const QString &);

    /*---<элементарные функции>---*/
    char ch();

    uchar get();

    char uch(bool);

    uchar getb(bool);

    template<typename T>
    char ch(T &);

    template<typename T>
    uchar get(T &);

    template<typename T>
    char uch(T &, bool);

    template<typename T>
    uchar getb(T &, bool);
    /*---</элементарные функции>---*/

    Byte_order get_BOM(bool);

    QString get_iso8859_str(bool, const long long &);

    QString get_utf16_str(bool, Byte_order, const long long &);//не чекает BOM

    QString get_utf8_str(bool, const long long &);

    QString get_ucs2_str(bool, Byte_order, const long long &);//не чекает BOM

    QString get_encoding_dependent_string(bool, String_encoding, const long long &, function<bool()>);

    QByteArray get_raw_bytes(bool, ulong);

    operator bool () const;

    const File_metadata & get_data() const;

    File_metadata & get_data();

    bool parse();

    void display_info(bool) const;

    bool has_info() const;

    void shift(long long = -1);

    void back_from_end(qint64);

    char ch_backwards();

    bool check_for(string);

    Tag_version v2_header();

    ulong parse_v2_footer();//возвращает 0, если футер не найден или некорректен

    void parse_from_start();

    void parse_from_end();

    void parse_v1();

    virtual ~Binary() override;
};

template<typename T>
uchar Binary::get(T & count)
{
    return ::get(getChar_lambda
                , count);
}

template<typename T>
char Binary::ch(T & count)
{
    return ::ch(getChar_lambda
                , count);
}

template<typename T>
uchar Binary::getb(T & count, bool unsynch)
{
    return ::getb(getChar_lambda
                , unsynch
                , one_byte_back_lambda
                , count);
}

template<typename T>
char Binary::uch(T & count, bool unsynch)
{
    return ::uch(getChar_lambda
                , unsynch
                , one_byte_back_lambda
                , count);
}
