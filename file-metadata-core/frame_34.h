#pragma once
#include "frame.h"
#include "file_contents.h"
using namespace std;

class Frame34 : public Frame
{
protected:
    Frame_status frame_status{};
    Frame_format frame_format{};
    mutable File_contents content{};//mutable - это костыль, который пришлось поставить, чтобы переопределить const virtual функцию
    unsigned long data_length{0};//длина информации без учёта расширенного заголовка

private:
    Frame34(const Frame34 &) = delete;//ЗАПРЕЩЕНО
    Frame34 & operator = (const Frame34 &) = delete;//ЗАПРЕЩЕНО

protected:
    void check_compression();

    virtual char ch() const override final;

    virtual uchar get() const override final;

    virtual char uch() const override final;

    virtual uchar getb() const override final;

    char ch(int &) const;

    uchar get(int &) const;

    char uch(int &) const;

    uchar getb(int &) const;

    virtual Byte_order get_BOM() const override final;

    virtual QString get_iso8859_str() const override final;

    virtual QString get_iso8859_str(const long long &) const override final;

    virtual QString get_utf16_str(Byte_order) const override final;//не чекает BOM

    virtual QString get_utf16_str(Byte_order, const long long &) const override final;//не чекает BOM

    virtual QString get_utf8_str() const override final;

    virtual QString get_utf8_str(const long long &) const override final;

    virtual QString get_ucs2_str(Byte_order) const override final;//не чекает BOM

    virtual QString get_ucs2_str(Byte_order, const long long &) const override final;//не чекает BOM

    virtual QString get_encoding_dependent_string(String_encoding) const override final;

    virtual QString get_encoding_dependent_string(String_encoding, const long long &) const override final;

    virtual QByteArray get_binary_till_end() const override final;

    virtual bool skip() const override final;

    virtual long long pos() const override final;

    virtual void seek(long long) const override final;

    virtual void shift(long long) const override final;

    virtual bool end() const override final;

    virtual long long size() const override final;

    virtual string get_symbols(int) override final;

    virtual bool tag_has_content() const = 0;

    virtual File_contents & tags_content() const = 0;

public:
    explicit Frame34(Tag &);

    uchar get_group_mark() const;

    Frame_format & get_format();

    Frame_status & get_status();

    const Frame_format & get_format() const;

    const Frame_status & get_status() const;

    virtual bool parse() override final;

    virtual ~Frame34() override;
};
