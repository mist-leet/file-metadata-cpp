#pragma once
#include "v23.h"
#include "frame_34.h"
using namespace std;

class Frame3 : public Frame34
{
    Frame3(const Frame3 &) = delete;//ЗАПРЕЩЕНО
    Frame3 & operator = (const Frame3 &) = delete;//ЗАПРЕЩЕНО

protected:
    Binary::V23 &tag;

    virtual bool parse_header() override final;

    virtual bool tagHasContent() const override final;

    virtual FileContents & tagsContent() const override final;

    virtual QString getEncodingDependentString(FileContents &) const override final;

    virtual QString getEncodingDependentString(FileContents &, const long long &) const override final;

    virtual QString getEncodingDependentString(bool) const override final;

    virtual QString getEncodingDependentString(bool, const long long &) const override final;

public:
    explicit Frame3(Binary::V23 &);

    static bool isGroupOrEncrMark(uchar);

    virtual ~Frame3() override;
};
