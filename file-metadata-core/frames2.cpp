#include "frames2.h"
using namespace std;

Binary::V22::unknown_frame::unknown_frame(Binary::V22 &tag)
    : Frame2(tag)
{}

Binary::V22::unknown_frame::~unknown_frame() = default;

bool Binary::V22::unknown_frame::parse_data()
{
    return skip();
}
