#pragma once
#include "v24.h"
using namespace std;

class Binary::V24::UnknownFrame : public Frame4
{
protected:
    virtual bool parseHeader() override final;
    virtual bool parseData() override final;

public:
    explicit UnknownFrame(Binary::V24 &t) : Frame4(t) {}
    virtual ~UnknownFrame() override = default;
};

class Binary::V24::PaddingHandler : public Frame4
{
protected:
    virtual bool parseHeader() override final;
    virtual bool parseData() override final;

public:
    explicit PaddingHandler(Binary::V24 &t) : Frame4(t) {}
    virtual ~PaddingHandler() override = default;
};
