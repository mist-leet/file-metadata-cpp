#pragma once
#include "frame4.h"
using namespace std;

//подпись для группы фреймов
class Binary::V24::SIGN : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit SIGN(Binary::V24 &t) : Frame4(t) {}
    virtual ~SIGN() override = default;
};

//BPM в разные моменты времени
class Binary::V24::SYTC : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit SYTC(Binary::V24 &t) : Frame4(t) {}
    virtual ~SYTC() override = default;
};

//текст/события, синхронизированные со временем
class Binary::V24::SYLT : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit SYLT(Binary::V24 &t) : Frame4(t) {}
    virtual ~SYLT() override = default;
};

//для поиска других тегов в файле
class Binary::V24::SEEK : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit SEEK(Binary::V24 &t) : Frame4(t) {}
    virtual ~SEEK() override = default;
};

//для поиска моментов времени в файле с переменным битрейтом
class Binary::V24::ASPI : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit ASPI(Binary::V24 &t) : Frame4(t) {}
    virtual ~ASPI() override = default;
};

//кодировка аудиоданных
class Binary::V24::AENC : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit AENC(Binary::V24 &t) : Frame4(t) {}
    virtual ~AENC() override = default;
};

//attached picture
class Binary::V24::APIC : public Frame4
{
protected:
    virtual bool parseData() override final;
public:
    explicit APIC(Binary::V24 &t) : Frame4(t) {}
    virtual ~APIC() override = default;
};
