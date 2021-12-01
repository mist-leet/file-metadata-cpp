#pragma once
#include "v23.h"
#include "frame_34.h"
using namespace std;

class Frame3 : public Frame34
{
    Frame3(const Frame3 &) = delete;//ЗАПРЕЩЕНО
    Frame3 & operator = (const Frame3 &) = delete;//ЗАПРЕЩЕНО

protected:
    Binary::V23 &tag;

    virtual bool parse_header() override final;

    virtual bool set_string_encoding() override final;

    uchar get_group_mark() const;

    virtual bool tag_has_content() const override final;

    virtual File_contents & tags_content() const override final;

public:
    explicit Frame3(Binary::V23 &);

    static bool is_group_or_encr_mark(uchar);

    virtual ~Frame3() override;
};
