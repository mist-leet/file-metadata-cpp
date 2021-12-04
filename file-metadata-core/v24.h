#pragma once
#include "tag34.h"
#include "frameparser.h"

class Binary::V24 : public Tag34
{
protected:
    Restrictions restrictions{};

    friend class FrameParser;

private:
    V24 (const V24 & ) = delete;
    V24 & operator = (const V24 &) = delete;

protected:
    virtual bool parseExtendedHeader() override final;
    virtual bool parseHeader() override final;
    virtual bool handleCrc() override final;
    virtual void actualParse() override final;

    bool setCrc();
    bool setRestrictions();

public:
    explicit V24(Binary &);//объект создаётся после проверки значений версии и ревизии

    static bool isUserdefTxt(const char *const);

    virtual ~V24() override;
};
