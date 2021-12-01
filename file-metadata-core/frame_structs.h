#pragma once

//v3-4
struct FrameStatus
{
    bool tagAlterPreservation{true};
    bool fileAlterPreservation{true};
    bool readOnly{false};

    FrameStatus()
    {}
};
