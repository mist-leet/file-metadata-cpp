#pragma once
#include "binary.h"
#include "easy_ptr.h"
using namespace std;

class File_contents
{
    void one_byte_back_with_no_check();

protected:
    QByteArray data{};
    ulong position{0};

    function<bool(char *)> getCharLambda{
                                            [this](char *c)
                                            {
                                                return this->getChar(c);
                                            }
                                        };

    function<void()> oneByteBackLambda{
                                            [this]()
                                            {
                                                return this->one_byte_back_with_no_check();
                                            }
                                      };

public:
    File_contents();

    bool set_data_and_check_src(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_crc);//file -> tag

    bool decompress_raw_data(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_data_size);//file -> frame

    bool decompress_raw_data(File_contents &other_storage, ulong raw_data_size, ulong expected_data_size);//tag -> frame

    QByteArray share_data(ulong size);

    bool getChar(char *);

    /*---<элементарные функции>---*/
    char ch();

    uchar get();

    template<typename T>
    char ch(T &);

    template<typename T>
    uchar get(T &);
    /*---</элементарные функции>---*/

    Byte_order get_BOM();

    QString get_iso8859_str();

    QString get_iso8859_str(const long long &);

    QString get_utf16_str(Byte_order);//не чекает BOM

    QString get_utf16_str(Byte_order, const long long &);//не чекает BOM

    QString get_utf8_str();

    QString get_utf8_str(const long long &);

    QString get_ucs2_str(Byte_order);//не чекает BOM

    QString get_ucs2_str(Byte_order, const long long &);//не чекает BOM

    QByteArray get_binary_till_end();

    QString get_encoding_dependent_string(String_encoding, function<bool()>);//не чекает BOM

    QString get_encoding_dependent_string(String_encoding, const long long &, function<bool()>);//не чекает BOM

    bool skip();

    ulong pos() const;

    void seek(ulong);

    void shift(long long = -1);

    bool end() const;

    int lastpos() const;

    int size() const;

    string get_symbols(int);

    string get_frame34_id();

    operator bool () const;

    virtual ~File_contents();
};

template<typename T>
char File_contents::ch(T &count)
{
    return ::ch(getCharLambda
                , count);
}

template<typename T>
uchar File_contents::get(T &count)
{
    return ::get(getCharLambda
                 , count);
}
