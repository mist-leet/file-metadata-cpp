#pragma once
#include "frame4.h"
using namespace std;

//метка метода шифровки
class Binary::V24::ENCR : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit ENCR(Binary::V24 &t) : Frame4(t){}
    virtual ~ENCR() override = default;
};

//тайминги событий в треке
class Binary::V24::ETCO : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit ETCO(Binary::V24 &t) : Frame4(t){}
    virtual ~ETCO() override = default;
};

//выравнивание звука
class Binary::V24::EQU2 : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit EQU2(Binary::V24 &t) : Frame4(t){}
    virtual ~EQU2() override = default;
};

//unique file id
class Binary::V24::UFID : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit UFID(Binary::V24 &t) : Frame4(t){}
    virtual ~UFID() override = default;
};

//владелец файла
class Binary::V24::USER : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit USER(Binary::V24 &t) : Frame4(t){}
    virtual ~USER() override = default;
};

//текст песни или что нибудь вокальное
class Binary::V24::USLT : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit USLT(Binary::V24 &t) : Frame4(t){}
    virtual ~USLT() override = default;
};

//что это
class Binary::V24::MLLT : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit MLLT(Binary::V24 &t) : Frame4(t){}
    virtual ~MLLT() override = default;
};

//дамп оглавления CD-диска, с которого был взят трек
class Binary::V24::MCDI : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit MCDI(Binary::V24 &t) : Frame4(t){}
    virtual ~MCDI() override = default;
};
