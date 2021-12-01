#pragma once
#include "frame4.h"
using namespace std;

//метка для группы фреймов
class Binary::V24::GRID : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit GRID(Binary::V24 &);

    virtual ~GRID() override;
};

//general object
class Binary::V24::GEOB : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit GEOB(Binary::V24 &);

    virtual ~GEOB() override;
};

//текстовая информация, не подходящая под другие фреймы
class Binary::V24::COMM : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit COMM(Binary::V24 &);

    virtual ~COMM() override;
};

//как купить трек
class Binary::V24::COMR : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit COMR(Binary::V24 &);

    virtual ~COMR() override;
};

//ремайндер или пруф о покупке трека
class Binary::V24::OWNE : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit OWNE(Binary::V24 &);

    virtual ~OWNE() override;
};

//ссылка на фрейм из другого файла
class Binary::V24::LINK : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit LINK(Binary::V24 &);

    virtual ~LINK() override;
};
