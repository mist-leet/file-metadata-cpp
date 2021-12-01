#pragma once
#include "easy_ptr.h"
using namespace std;

//v3-4
struct Frame_status
{
    bool tag_alter_preservation{true};
    bool file_alter_preservation{true};
    bool read_only{false};

    Frame_status()
    {}
};

//v3-4
struct Frame_format
{
    bool group_id_presence{false};
    uchar group_id;
    bool encryption{false};
    uchar encryption_method_marker;
    pair<ulong,bool> compression_info{make_pair(0,false)};//first is uncompressed size

    Frame_format()
    {}
};
