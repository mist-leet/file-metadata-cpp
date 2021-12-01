#pragma once
#include "tag34.h"
#include "frameparser.h"

class Binary::V23 : public Tag34
{
    friend class FrameParser;

    ulong sizeOfPadding{0};

    V23 (const V23 &) = delete;
    V23 & operator = (const V23 &) = delete;

protected:
    virtual bool parseExtendedHeader() override final;
    virtual bool parseHeader() override final;
    virtual void actualParse() override final;

    virtual bool handleCrc() override final;

public:
    explicit V23(Binary &);//объект создаётся после проверки значений версии и ревизии

    static bool isUserdefTxt(const char *const);

    virtual ~V23() override;
};
