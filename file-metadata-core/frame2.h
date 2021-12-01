#pragma once
#include "v22.h"
#include "frame.h"
using namespace std;

class Frame2 : public Frame
{
    Frame2(const Frame2 &) = delete;
    Frame2 & operator = (const Frame2 &) = delete;

protected:
    Binary::V22 &tag;

    virtual bool parse_header() override final;

    virtual bool set_string_encoding() override final;

public:
    explicit Frame2(Binary::V22 &);

    virtual bool parse() override final;

    virtual ~Frame2() override;
};
