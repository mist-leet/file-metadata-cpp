#pragma once
#include "file-holder.h"

class Binary::V1 : public FileHolder
{
protected:
    virtual bool parseData() override final;
    virtual bool parseHeader() override final;

    QString getField(int) const;

public:
    explicit V1(Binary &);

    virtual bool parse() override final;

    virtual ~V1() override;
};
