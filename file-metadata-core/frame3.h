#pragma once
#include "v23.h"
#include "frame2.h"
using namespace std;

class Binary::V23::Frame3 : public Binary::V22::Frame2
{
protected:
    Frame_status frame_status;
    Frame_format frame_format;
    unsigned long data_length;//длина информации без учёта расширенных данных фрейма
    Encryption_method_markers encryption_info;

private:
    Frame3(const Frame3 &) = delete;//ЗАПРЕЩЕНО
    Frame3 & operator = (const Frame3 &) = delete;//ЗАПРЕЩЕНО

    Group_markers_3 grouping_info;

protected:
    virtual bool parse_frame_header() override;

    virtual bool parse_frame_data() override = 0;

public:
    explicit Frame3(Binary::V23 & tag) :
        Frame2(tag),
        frame_format(Frame_format()),
        data_length(0)
    {
        start_position = pos() - 4;
    }

    virtual bool parse_frame() override;

    virtual ~Frame3() override;//определить
};
