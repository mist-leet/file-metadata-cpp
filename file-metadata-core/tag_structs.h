#pragma once
#include "easy_ptr.h"
using namespace std;

//ограничения для тега v2.4
struct Restrictions
{
    bool presence{false};
    ulong max_size{268435455};
    ulong max_frames{24403223};
    //false - нет ограничений, true - только ISO-8859-1 или UTF-8
    bool encoding_rest{false};
    ulong max_char_per_frame{268435445};
    //false - нет ограничений, true - только PNG или JPEG[JFIF]
    bool image_encoding_rest{false};

    /* 00 - нет ограничений
     * 01 - 256х256 пкс или менее
     * 10 - 64х64 пкс или менее
     * 11 - строго 64х64 пкс
    */
    pair<bool,bool> image_size_rest;

    Restrictions()
        : image_size_rest(make_pair(false,false))
    {}

    operator bool() const {return presence;}
};

struct Group_markers
{
    QHash<unsigned char, QString> url;
    QHash<unsigned char, QByteArray> info;
    QHash<unsigned char, QByteArray> sign;
};

struct Encryption_method_markers
{
    QHash<unsigned char, QString> url;
    QHash<unsigned char, QByteArray> info;
};
