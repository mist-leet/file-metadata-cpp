#pragma once
#include "v22.h"
using namespace std;

//класс, от которого будут наследоваться классы для фреймов V2.2, V2.3 и V2.4
class Binary::V22::Frame2 : public File_holder
{
    Frame2(const Frame2 &) = delete;
    Frame2 & operator = (const Frame2 &) = delete;

protected:
    virtual bool parse_frame_header();

    virtual bool parse_frame_data() = 0;

public:
    explicit Frame2(Binary::V22 & tag) :
        File_holder(tag.file, tag.unsynch)
    {}

    virtual bool parse_frame();

    virtual ~Frame2();//определить
};
