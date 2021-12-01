#pragma once
#include "file-holder.h"

class Tag : public FileHolder
{
    Tag(const Tag &) = delete;
    Tag & operator= (const Tag &) = delete;

protected:
    long long extremePositionOfFrame{endPosition};

    virtual std::string getFrameId() = 0;

public:
    explicit Tag(Binary &);

    static bool correctChar(char);

    static bool correctChar(uchar);

    virtual ~Tag() override;
};
