#pragma once
#include "file-holder.h"
#include "tag.h"
using namespace std;

class Frame : public File_holder
{
protected:
    String_encoding encoding{not_given};

private:
    Frame(const Frame &) = delete;
    Frame & operator = (const Frame &) = delete;

protected:
    virtual bool set_string_encoding() = 0;

    QString get_url() const;

    QString get_url(const long long &) const;

public:
    explicit Frame(Tag &);

    virtual ~Frame() override;
};
