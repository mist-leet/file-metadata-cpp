#pragma once
#include "frame2.h"
using namespace std;

class Binary::V22::unknown_frame : public Frame2
{
protected:
    bool parse_data() override final;

public:
    unknown_frame(Binary::V22 &);

    ~unknown_frame() override;
};
