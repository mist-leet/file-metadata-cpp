#pragma once
#include "v24.h"
using namespace std;

class Binary::V24::unknown_frame : public Frame4
{
protected:
    virtual bool parse_header() override final;

    virtual bool parse_data() override final;

public:
    unknown_frame(Binary::V24 &);

    ~unknown_frame() override;
};

class Binary::V24::padding_handler : public Frame4
{
protected:
    virtual bool parse_header() override final;

    virtual bool parse_data() override final;

public:
    padding_handler(Binary::V24 &);

    ~padding_handler() override;
};
