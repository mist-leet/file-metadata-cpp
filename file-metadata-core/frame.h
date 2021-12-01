#pragma once
#include "file-holder.h"
#include "tag.h"
using namespace std;

class Frame : public FileHolder
{
    Frame(const Frame &) = delete;
    Frame & operator = (const Frame &) = delete;

protected:
    QString getUrl() const;

    QString getUrl(const long long &) const;

    virtual QString getEncodingDependentString() const = 0;

    virtual QString getEncodingDependentString(const long long &) const = 0;

public:
    explicit Frame(Tag &);

    virtual ~Frame() override;
};
