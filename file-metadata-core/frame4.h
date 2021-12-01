#pragma once
#include "v24.h"
#include "frame3.h"
using namespace std;

class Binary::V24::Frame4 : public Binary::V23::Frame3
{
protected:
    Group_markers_4 grouping_info;

private:
    Frame4(const Frame4 &) = delete;//ЗАПРЕЩЕНО
    Frame4 & operator = (const Frame4 &) = delete;//ЗАПРЕЩЕНО

protected:
    virtual bool parse_frame_header() override;

    bool set_length();

    virtual bool parse_frame_data() override = 0;

public:
    explicit Frame4(Binary::V24 & tag) :
        Frame3(tag)
    {}

    virtual ~Frame4() override;
};
