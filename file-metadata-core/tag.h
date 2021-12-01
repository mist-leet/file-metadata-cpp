#pragma once
#include "file-holder.h"
using namespace std;

class Tag : public File_holder
{
    Tag(const Tag &) = delete;
    Tag & operator= (const Tag &) = delete;

protected:
    long long extreme_position_of_frame{end_position};

    virtual string get_frame_id() = 0;

public:
    explicit Tag(Binary & file);

    static bool correct_char(char);

    static bool correct_char(uchar);

    virtual ~Tag() override;
};
