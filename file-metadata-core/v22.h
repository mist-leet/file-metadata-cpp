#pragma once
#include "tag.h"
#include "frameparser.h"

class Binary::V22 : public Tag
{
    friend class FrameParser;

    V22 (const V22 &) = delete;
    V22 & operator = (const V22 &) = delete;

protected:
    virtual bool parseHeader() override final;
    virtual bool parseData() override final;

    virtual std::string getFrameId() override final;

public:
    explicit V22(Binary &);//объект создаётся после проверки значений версии и ревизии

    static bool isUserdefTxt(const char *const);
    static bool isUserdefUrl(const char *const);
    static bool isFreeFrame(const char *const);
    static bool correctId(const char *const);

    virtual ~V22() override;
};
