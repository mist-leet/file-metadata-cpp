#pragma once
#include "file-holder.h"

class TagParser
{
    TagParser & operator = (const TagParser &) = delete;
    TagParser(const TagParser &) = delete;

    FileHolder *tag{nullptr};

public:
    TagParser(Binary &);//V1
    TagParser(TagVersion, Binary &);//V2*

    ParsingResult parse() const;

    ~TagParser();
};
