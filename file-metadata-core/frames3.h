#pragma once
#include "frame3.h"
using namespace std;

class Binary::V23::UnknownFrame : public Frame3
{
protected:
    virtual bool parseHeader() override final;
    virtual bool parseData() override final;

public:
    explicit UnknownFrame(Binary::V23 &t) : Frame3(t) {}
    virtual ~UnknownFrame() override = default;
};

class Binary::V23::PaddingHandler : public Frame3
{
protected:
    virtual bool parseHeader() override final;
    virtual bool parseData() override final;

public:
    explicit PaddingHandler(Binary::V23 &t) : Frame3(t) {}
    virtual ~PaddingHandler() override = default;
};
