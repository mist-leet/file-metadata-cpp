#pragma once
#include "frame4.h"
using namespace std;

//метка для группы фреймов
class Binary::V24::GRID : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit GRID(Binary::V24 &t) : Frame4(t) {}
    virtual ~GRID() override = default;
};

//general object
class Binary::V24::GEOB : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit GEOB(Binary::V24 &t) : Frame4(t) {}
    virtual ~GEOB() override = default;
};

//текстовая информация, не подходящая под другие фреймы
class Binary::V24::COMM : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit COMM(Binary::V24 &t) : Frame4(t) {}
    virtual ~COMM() override = default;
};

//как купить трек
class Binary::V24::COMR : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit COMR(Binary::V24 &t) : Frame4(t) {}
    virtual ~COMR() override = default;
};

//ремайндер или пруф о покупке трека
class Binary::V24::OWNE : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit OWNE(Binary::V24 &t) : Frame4(t) {}
    virtual ~OWNE() override = default;
};

//ссылка на фрейм из другого файла
class Binary::V24::LINK : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit LINK(Binary::V24 &t) : Frame4(t) {}
    virtual ~LINK() override = default;
};
