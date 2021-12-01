#pragma once
#include "v24.h"
#include "frame_34.h"
using namespace std;

class Frame4 : public Frame34
{
    Frame4(const Frame4 &) = delete;//ЗАПРЕЩЕНО
    Frame4 & operator = (const Frame4 &) = delete;//ЗАПРЕЩЕНО

protected:
    Binary::V24 &tag;

    virtual bool parseHeader() override;

    uchar getGroupMark() const;

    virtual bool tagHasContent() const override final;

    virtual FileContents & tagsContent() const override final;

    virtual QString getEncodingDependentString(FileContents &) const override final;

    virtual QString getEncodingDependentString(FileContents &, const long long &) const override final;

    virtual QString getEncodingDependentString(bool) const override final;

    virtual QString getEncodingDependentString(bool, const long long &) const override final;

public:
    explicit Frame4(Binary::V24 &);

    static bool isGroupOrEncrMark(uchar);

    virtual ~Frame4() override;
};
