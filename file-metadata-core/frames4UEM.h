#pragma once
#include "frame4.h"
using namespace std;

//метка метода шифровки
class Binary::V24::ENCR : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit ENCR(Binary::V24 &);

    virtual ~ENCR() override;
};

//тайминги событий в треке
class Binary::V24::ETCO : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit ETCO(Binary::V24 &);

    virtual ~ETCO() override;
};

//выравнивание звука
class Binary::V24::EQU2 : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit EQU2(Binary::V24 &);

    virtual ~EQU2() override;
};

//владелец файла
class Binary::V24::USER : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit USER(Binary::V24 &);

    virtual ~USER() override;
};

//текст песни или что нибудь вокальное
class Binary::V24::USLT : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit USLT(Binary::V24 &);

    virtual ~USLT() override;
};

//что это
class Binary::V24::MLLT : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit MLLT(Binary::V24 &);

    virtual ~MLLT() override;
};

//дамп оглавления CD-диска, с которого был взят трек
class Binary::V24::MCDI : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit MCDI(Binary::V24 &);

    virtual ~MCDI() override;
};
