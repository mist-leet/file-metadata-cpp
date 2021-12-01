#pragma once
#include "frame3.h"
using namespace std;

class Binary::V23::unknown_frame : public Frame3
{
protected:
    virtual bool parse_header() override final;

    virtual bool parse_data() override final;

public:
    unknown_frame(Binary::V23 &);

    ~unknown_frame() override;
};

class Binary::V23::padding_handler : public Frame3
{
protected:
    virtual bool parse_header() override final;

    virtual bool parse_data() override final;

public:
    padding_handler(Binary::V23 &);

    ~padding_handler() override;
};
