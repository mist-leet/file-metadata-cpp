#pragma once
#include "frame4.h"
using namespace std;

//пользовательская регулировка громкости
class Binary::V24::RVA2 : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit RVA2(Binary::V24 &t) : Frame4(t) {}
    virtual ~RVA2() override = default;
};

//регулировка эха
class Binary::V24::RVRB : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit RVRB(Binary::V24 &t) : Frame4(t) {}
    virtual ~RVRB() override = default;
};

//кол-во проигрываний
class Binary::V24::PCNT : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit PCNT(Binary::V24 &t) : Frame4(t) {}
    virtual ~PCNT() override = default;
};

//популярность
class Binary::V24::POPM : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit POPM(Binary::V24 &t) : Frame4(t) {}
    virtual ~POPM() override = default;
};
