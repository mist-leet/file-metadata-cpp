#pragma once
#include "file-holder.h"
using namespace std;

//тег v2.2, от которого будут наследоваться теги v2.3 и v2.3
class Binary::V22 : public File_holder
{
    V22 (const V22 & ) = delete;
    V22 & operator = (const V22 &) = delete;

    class Frame2;
    friend class Binary::V22::Frame2;

    friend class Binary::V23;

    friend class Binary;

protected:
    virtual bool parse_header();

    bool set_length();//вызывается только с позиции, с которой в заголовке фрейма идут байты длины

public:
    explicit V22(Binary & file_) ://объект создаётся после проверки значений версии и ревизии
        File_holder(file_)
    {}

    virtual bool parse();

    virtual ~V22() = default;
};
