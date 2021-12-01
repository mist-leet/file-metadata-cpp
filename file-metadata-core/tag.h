#pragma once
#include "file-holder.h"
using namespace std;

class Tag : public FileHolder
{
    Tag(const Tag &) = delete;
    Tag & operator= (const Tag &) = delete;

protected:
    long long extremePositionOfFrame{endPosition};

    virtual string getFrameId() = 0;

public:
    explicit Tag(Binary & file);

    static bool correctChar(char);

    static bool correctChar(uchar);

    virtual ~Tag() override;
};
