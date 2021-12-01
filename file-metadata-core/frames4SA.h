#pragma once
#include "frame4.h"
using namespace std;

//подпись для группы фреймов
class Binary::V24::SIGN : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit SIGN(Binary::V24 &);

    virtual ~SIGN() override;
};

//BPM в разные моменты времени
class Binary::V24::SYTC : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit SYTC(Binary::V24 &);

    virtual ~SYTC() override;
};

//текст/события, синхронизированные со временем
class Binary::V24::SYLT : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit SYLT(Binary::V24 &);

    virtual ~SYLT() override;
};

//для поиска других тегов в файле
class Binary::V24::SEEK : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit SEEK(Binary::V24 &);

    virtual ~SEEK() override;
};

//для поиска моментов времени в файле с переменным битрейтом
class Binary::V24::ASPI : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit ASPI(Binary::V24 &);

    virtual ~ASPI() override;
};

//кодировка аудиоданных
class Binary::V24::AENC : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit AENC(Binary::V24 &);

    virtual ~AENC() override;
};

//attached picture
class Binary::V24::APIC : public Frame4
{
protected:
    virtual bool parse_data() override final;

public:
    explicit APIC(Binary::V24 &);

    virtual ~APIC() override;
};
