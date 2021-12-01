#pragma once
#include "tag.h"
using namespace std;

class Binary::V1 : public File_holder
{
protected:
    virtual bool parse_data() override final;

    virtual bool parse_header() override final;

    QString get_field(int) const;

public:
    explicit V1(Binary & f);

    virtual bool parse() override final;

    virtual ~V1() override;
};
