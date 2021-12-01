#pragma once
#include "easy_ptr.h"
using namespace std;

//v3-4
struct FrameStatus
{
    bool tagAlterPreservation{true};
    bool fileAlterPreservation{true};
    bool readOnly{false};

    FrameStatus()
    {}
};

//v3-4
struct FrameFormat
{
    bool groupIdPresence{false};
    uchar groupId;
    bool encryption{false};
    uchar encryptionMethodMarker;
    pair<ulong,bool> compressionInfo{make_pair(0,false)};//first is uncompressed size

    FrameFormat()
    {}
};
