#pragma once
#include "v24.h"
#include "frame_34.h"
using namespace std;

class Frame4 : public Frame34
{
    Frame4(const Frame4 &) = delete;//ЗАПРЕЩЕНО
    Frame4 & operator = (const Frame4 &) = delete;//ЗАПРЕЩЕНО

protected:
    Binary::V24 &tag;

    virtual bool parse_header() override;

    virtual bool set_string_encoding() override final;

    uchar get_group_mark() const;

    virtual bool tag_has_content() const override final;

    virtual File_contents & tags_content() const override final;

public:
    explicit Frame4(Binary::V24 &);

    static bool is_group_or_encr_mark(uchar);

    virtual ~Frame4() override;
};
