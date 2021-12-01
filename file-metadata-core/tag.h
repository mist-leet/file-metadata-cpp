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

    template<typename T, class = std::enable_if_t<anyChar<T>>>
    static bool correctChar(T);

    virtual ~Tag() override;
};

template<typename T, class >
bool Tag::correctChar(T c) {
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
