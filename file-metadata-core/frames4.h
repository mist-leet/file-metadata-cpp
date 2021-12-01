#pragma once
#include "frame4.h"
using namespace std;

//PRIV, RBUF, X..., Y..., Z...
class Binary::V24::unknown_frame : public Binary::V24::Frame4
{
public:
    explicit unknown_frame(Binary::V24 & tag) :
        Frame4(tag)
    {}

    virtual bool parse_frame_data() override;

    virtual ~unknown_frame() override = default;
};

//подпись для группы фреймов
class Binary::V24::SIGN_4 : public Binary::V24::Frame4
{
public:
    explicit SIGN_4(Binary::V24 & tag) :
        Frame4(tag)
    {}

    virtual bool parse_frame_data() override;

    virtual ~SIGN_4() override = default;
};

//метка для группы фреймов
class Binary::V24::GRID_4 : public Binary::V24::Frame4
{
public:
    explicit GRID_4(Binary::V24 & tag) :
        Frame4(tag)
    {}

    virtual bool parse_frame_data() override;

    virtual ~GRID_4() override = default;
};

//метка метода шифровки
class Binary::V24::ENCR_4 : public Binary::V24::Frame4
{
public:
    explicit ENCR_4(Binary::V24 & tag) :
        Frame4(tag)
    {}

    virtual bool parse_frame_data() override;

    virtual ~ENCR_4() override = default;
};
