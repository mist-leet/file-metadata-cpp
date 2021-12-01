#pragma once
#include "file-holder.h"

class Frame : public FileHolder
{
    Frame(const Frame &) = delete;
    Frame & operator = (const Frame &) = delete;

protected:
    virtual void extract();
    virtual bool parseData() override;

    void setTextField(QString) const;
    void setString(QString &) const;

    virtual QString getEncodingDependentString() const = 0;
    virtual QString getEncodingDependentString(ulong) const = 0;

public:
    Frame(Binary&, bool);
    virtual ~Frame() override;
};
