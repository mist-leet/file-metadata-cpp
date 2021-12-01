#pragma once
#include "pch.h"

//ограничения для тега v2.4
struct Restrictions
{
    bool presence{false};
    ulong maxSize{268435455};
    ulong maxFrames{24403223};
    //false - нет ограничений, true - только ISO-8859-1 или UTF-8
    bool encodingRest{false};
    ulong maxCharPerFrame{268435445};
    //false - нет ограничений, true - только PNG или JPEG[JFIF]
    bool imageEncodingRest{false};

    /* 00 - нет ограничений
     * 01 - 256х256 пкс или менее
     * 10 - 64х64 пкс или менее
     * 11 - строго 64х64 пкс
    */
    std::pair<bool,bool> imageSizeRest{std::make_pair(false,false)};

    Restrictions()
    {}

    operator bool() const {
        return presence;
    }
};
