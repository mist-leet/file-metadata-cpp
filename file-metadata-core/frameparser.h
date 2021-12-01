#pragma once
#include "frame2.h"
#include "frame3.h"
#include "frame4.h"

class FrameParser
{
    FrameParser & operator = (const FrameParser &) = delete;
    FrameParser(const FrameParser &) = delete;

    Frame *frame{nullptr};

public:

    FrameParser(const char *const, Binary::V22 &);//frame 2
    FrameParser(const char *const, Binary::V23 &);//frame 3
    FrameParser(const char *const, Binary::V24 &);//frame 4

    ParsingResult parse() const;

    ~FrameParser();
};
