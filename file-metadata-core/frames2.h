#pragma once
#include "frame2.h"
using namespace std;

class Binary::V22::UnknownFrame : public Frame2
{
protected:
    bool parseData() override final;
public:
    explicit UnknownFrame(Binary::V22 &t) : Frame2(t) {}
    virtual ~UnknownFrame() override = default;
};
